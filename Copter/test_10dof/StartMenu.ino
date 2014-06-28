char TempString[10];
void startMenu(){
  while(1){ 
    if(charAvail()){
      char c = readCharTimeout(timeout);
      
      if(c == 'E'){  //using '!' as terminating string symbol
        sendChar('E');
      }
      else if(c == 't'){
        if(testConnectionBMP()){
       
        updateTemperature();
         
        for(int i=0; i<10; i++)
          TempString[i] = '\0';
        
        dtostrf(temperature,1,1,TempString);
        RFSerial.print(TempString);
        sendChar('!');
        }
        else{
           RFSerial.print("OFFLINE!");
           
           
        }    
       }
       else if(c == 'a'){
           if(testConnectionBMP()){
          
          updateAltitude();
         
         for(int i=0; i<10; i++)
          TempString[i] = '\0';
        
        dtostrf(altitude,1,1,TempString);
         Serial.println(TempString);
        RFSerial.print(TempString);
        sendChar('!');
        }
        else{
           RFSerial.print("OFFLINE!");
           
           
        }
       } 
       else if(c == 'd'){
         if(testConnectionHC()){
           RFSerial.print("ONLINE!");
         /* updateDistance();
          dtostrf(distance*10,2,2,TempString);
        RFSerial.print(TempString);*/
        }
        else{
          RFSerial.print("OFFLINE!");
        }
       }
       else if(c == 'h') //return heading
       {
         if(testConnectionHMC()){
           updateHeading();
           updateHeading();
          for(int i=0; i<10; i++)
            TempString[i] = '\0';
          dtostrf(heading,1,1,TempString);
       
          RFSerial.print(TempString);
          sendChar('!');
         }
         else{
           RFSerial.print("OFFLINE!");
         }
       }
       else if(c == 'p') //return pitch
       {
         if(testConnectionMPU()){
           
           handleInterrupt();
           updateYawPitchRoll();

          for(int i=0; i<10; i++)
            TempString[i] = '\0';
          dtostrf(pitch,1,1,TempString);
       
          RFSerial.print(TempString);
          sendChar('!');
         }
         else{
           RFSerial.print("OFFLINE!");
         }
       }
       else if(c == 'r') //return pitch
       {
         if(testConnectionMPU()){
           handleInterrupt();
             updateYawPitchRoll();
          for(int i=0; i<10; i++)
            TempString[i] = '\0';
          dtostrf(roll,1,1,TempString);
       
          RFSerial.print(TempString);
          sendChar('!');
         }
         else{
           RFSerial.print("OFFLINE!");
         }
       }
       else if(c == 'x'){ // return calibrated x-value (x acc offset)
         sendChar('a');
         RFSerial.println(String(calibrateMPU_Pitch0()));
         sendChar('!');
       }
       else if(c == 'y'){ // return calibrated y-value (y acc offset)
         sendChar('a');
         RFSerial.println(String(calibrateMPU_Roll0()));
         sendChar('!');
       }
       else if(c == 'c'){
         Serial.println("received: " + c);
         sendChar('a');
         calibrateMotors();
       }
    }
  }
}
