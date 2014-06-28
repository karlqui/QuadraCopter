void readStringRF(char (&readS)[20],int timeOutDelay);
bool calibrated;
void setupCalibrateMPUMenu(){
  calibrated = false;
   EsploraTFT.background(0,0,0); //clear screen
  createButton(EsploraTFT.width() - 50, EsploraTFT.height() - 30, 40, 20, "Back", 1, 0);
   EsploraTFT.text("Place the copter on (0,0)", 5, 10);
   EsploraTFT.text("switch 1 -> calibrate MPU", 5, 25);
   EsploraTFT.text("Pitch-offset:", 5, 70);
   EsploraTFT.text("Roll-offset:", 5, 80);
}
String calRoll, calPitch;
void checkCalibrateMPUMenu(){
  int button = Esplora.readJoystickSwitch();
  int s1 = Esplora.readButton(SWITCH_1);
  if(s1 == LOW){
    calibrated = true;
    EsploraTFT.stroke(255,0,0);
    EsploraTFT.text("Processing:", 90, 70);
   EsploraTFT.text("Processing:", 90, 80); 
    if(calibratePitch()){
      calPitch = readS;
      EsploraTFT.stroke(0,0,0);
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(90, 70, 100, 10);
      EsploraTFT.stroke(0,255,0);
      EsploraTFT.text(readS, 90, 70);
      calibrateRoll();
      calRoll = readS;
      EsploraTFT.stroke(0,0,0);
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(90, 80, 100, 10);
      EsploraTFT.stroke(0,255,0);
      EsploraTFT.text(readS, 90, 80);
      EsploraTFT.text("switch 3 -> save to EEPROM", 5, 40);
      EsploraTFT.stroke(255,255,255);
    }
    else{
      EsploraTFT.stroke(0,0,0);
      EsploraTFT.fill(0,0,0);
      EsploraTFT.rect(90, 70, 100, 10);
      EsploraTFT.rect(90, 80, 100, 10);
      EsploraTFT.stroke(255,0,0);
      EsploraTFT.text("NO COM", 90, 70);
      EsploraTFT.text("NO COM", 90, 80);
      
    }
    
  }
  int s3 = Esplora.readButton(SWITCH_3);
  if(s3 == LOW && calibrated){ //save received values to EEPROM
    saveEEPROM("CALPITCH", calPitch.toInt());
    saveEEPROM("CALROLL", calRoll.toInt());
  }
  if(button == LOW){
    setCurrentMenu(0);
    setupStartMenu();
  }
}

bool calibratePitch(){
  sendChar('x');
  for(int i=0; i<20; i++){
        readS[i] = '\0';
  }
  char c = readCharTimeout(timeout); //check comm
  if(c =='a'){
    Serial.println("Ack");
    readStringRF(readS, 20000); //it might take a long time to calibrate
    Serial.println(String(readS));
    return true;
  }
  else
    return false;
}
bool calibrateRoll(){
  sendChar('y');
  for(int i=0; i<20; i++){
        readS[i] = '\0';
  }
    char c = readCharTimeout(timeout); //check comm
  if(c =='a'){
  Serial.println("ack");
  readStringRF(readS, 20000);
  Serial.println(readS);
  return true;
  }
  else
    return false;
}
