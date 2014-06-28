



MPU6050 mpu;

bool MPUIsInit = false; 
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
double calibrationThreshold = 0.1;
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements

VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector




volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

bool checkDMP(){
  return dmpReady;
}

bool testConnectionMPU(){
  return mpu.testConnection();
}

int calibrateMPU_Pitch0(){//calibra 0 value on accelerometer
  bool success = false;
   //5 consecutive samples must be betweed 0.05 and -0.05
   while(!success){
   success = true;
   for(int i=0; i<8;i++){ //8 consecutive samples must be within the threshhold value
    while(checkInterrupt());
    handleInterrupt();
    updateYawPitchRoll();
    if(pitch<-0.01)
      mpu.setXAccelOffset(mpu.getXAccelOffset() + 1);
    else if(pitch>0.01)
      mpu.setXAccelOffset(mpu.getXAccelOffset() - 1);
    
    if(pitch>calibrationThreshold || pitch < -calibrationThreshold)
      success = false;
    delay(50);
   }
  
#ifdef PRINT_CAL_PITCH
  Serial.println(pitch);
  Serial.println(success);
#endif
  }
  return mpu.getXAccelOffset();
}

int calibrateMPU_Roll0(){
  bool success = false;
   //5 consecutive samples must be betweed 0.05 and -0.05
   while(!success){
   success = true;
   for(int i=0; i<8;i++){ //8 consecutive samples must be within the threshhold value
    while(checkInterrupt());
    handleInterrupt();
    updateYawPitchRoll();
      if(roll<-0.01)
    mpu.setYAccelOffset(mpu.getYAccelOffset() + 1);
  else if(roll>0.01)
    mpu.setYAccelOffset(mpu.getYAccelOffset() - 1);
    
    if(roll>calibrationThreshold || roll < -calibrationThreshold)
      success = false;

    delay(50);
    }
#ifdef PRINT_CAL_ROLL
Serial.println(roll);
Serial.println(success);
#endif
   }
   return mpu.getYAccelOffset();
}

void setupMPU6050(){
    mpu.initialize();
    
    MPUIsInit = mpu.testConnection();
    printDebugMessage(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    
    printDebugMessage(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();



    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        printDebugMessage(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        printDebugMessage(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        printDebugMessage(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        printDebugMessage(F("DMP Initialization failed (code "));
        printDebugMessage((String)devStatus);
        
    }
    mpu.setI2CBypassEnabled(true);
}

bool checkInterrupt(){
  return (!mpuInterrupt && fifoCount < packetSize);
}

void updateYawPitchRoll(){
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        
        yaw = ypr[0] * 180/M_PI;
        pitch = ypr[1] * 180/M_PI;
        roll = ypr[2] * 180/M_PI;
        
#ifdef PRINT_YAW
        Serial.print("Yaw:  ");
        Serial.println(yaw);
#endif

#ifdef PRINT_PITCH

        Serial.print("Pitch:  ");
        Serial.println(pitch);
#endif

#ifdef PRINT_ROLL
        Serial.print("Roll:  ");
        Serial.println(roll);
#endif

}

void updateWorldAccel(){
         // display initial world-frame acceleration, adjusted to remove gravity
            // and rotated based on known orientation from quaternion
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
            
#ifdef PRINT_WORLDACCEL 
            Serial.print("aworld X Y Z\t");
            Serial.print(aaWorld.x);
            Serial.print("\t");
            Serial.print(aaWorld.y);
            Serial.print("\t");
            Serial.println(aaWorld.z);
#endif
}

bool handleInterrupt(){
  
  
    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        return true;

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;
        return false;
        


    }

}

void mpuBypass(bool b){
  mpu.setI2CBypassEnabled(b);
}








