void readStringRF(char (&readS)[20],int timeOutDelay);



char temperature[20], altitude[20], pitch[20], roll[20];

void setupSensorMenu(bool clearScreen){
  if(clearScreen)
    EsploraTFT.background(0,0,0);
    
  createButton(EsploraTFT.width() - 50, EsploraTFT.height() - 30, 40, 20, "Back", 1, 0);
  EsploraTFT.textSize(1);
  EsploraTFT.text("BMP_180: ", 10, 30);
  EsploraTFT.text("HC_SR04: ", 10, 50);
  EsploraTFT.text("HMC5883L: ", 10, 70);
  EsploraTFT.text("MPU6050: ", 10, 90);

 for(int i=0; i<20; i++){
        readS[i] = '\0';
      }
  sendChar('t'); //get  temp
  readStringRF(readS, timeout);
  if(String(readS)==("ERROR")){
    EsploraTFT.text("BMP_180: NO COM", 10, 30);
  }
  else{
    
    
    if(String(readS) != "OFFLINE"){
         sendChar('a'); //get Alt
      for(int i=0; i<20; i++){
        temperature[i] = readS[i];
        readS[i] = '\0';
      }

      readStringRF(readS,timeout);
      
      
      if(String(readS) == "OFFLINE"){
        EsploraTFT.stroke(255,0,0);
        EsploraTFT.text(readS, 60, 30);
        EsploraTFT.stroke(255,255,255);
      }
      else{
        for(int i=0; i<20; i++){
        altitude[i] = readS[i];
        }
        EsploraTFT.text("T: ", 60, 30);
        if(!clearScreen){
          EsploraTFT.stroke(0,0,0);
          EsploraTFT.fill(0,0,0);
          EsploraTFT.rect(70, 30, 25, 15);
          EsploraTFT.stroke(255,255,255);
        }
        EsploraTFT.text(temperature, 70, 30);
        EsploraTFT.text("Alt: ", 97, 30);
        if(!clearScreen){
          EsploraTFT.stroke(0,0,0);
          EsploraTFT.fill(0,0,0);
          EsploraTFT.rect(120, 30, 30, 15);
          EsploraTFT.stroke(255,255,255);
        }
        EsploraTFT.text(altitude, 124, 30);
      
      }
      
    }
    else{
      EsploraTFT.stroke(255,0,0);
      EsploraTFT.text(readS, 60, 30);
      EsploraTFT.stroke(255,255,255);
    }
  }
  for(int i=0; i<20; i++){
        readS[i] = '\0';
      }
  sendChar('d');
  readStringRF(readS, timeout);
  if(String(readS) == "ERROR"){
    EsploraTFT.text("HC_SR04: NO COM", 10, 50);
  }
  else{
    if(String(readS) != "OFFLINE"){
    EsploraTFT.text(readS, 60, 50);
    }
    else{
      EsploraTFT.stroke(255,0,0);
      EsploraTFT.text(readS, 60, 50);
      EsploraTFT.stroke(255,255,255);
    }
  
  }
  
   for(int i=0; i<20; i++){
        readS[i] = '\0';
      }
  sendChar('h');
  readStringRF(readS, timeout);
  if(String(readS) == "ERROR"){
    EsploraTFT.text("HMC5883L: NO COM", 10, 70);
  }
  else{
    if(String(readS) != "OFFLINE"){
        EsploraTFT.text("Heading: ", 65, 70);
        if(!clearScreen){
          EsploraTFT.stroke(0,0,0);
          EsploraTFT.fill(0,0,0);
          EsploraTFT.rect(110, 70, 40, 15);
          EsploraTFT.stroke(255,255,255);
        }
        EsploraTFT.text(readS, 115, 70);
    }
    else{
      EsploraTFT.stroke(255,0,0);
      EsploraTFT.text(readS, 65, 70);
      EsploraTFT.stroke(255,255,255);
    }
  }
  
  for(int i=0; i<20; i++){
        readS[i] = '\0';
      }
  sendChar('p'); //get  pitch
  readStringRF(readS, timeout);
  if(String(readS)==("ERROR")){
    EsploraTFT.text("MPU6050: NO COM", 10, 90);
  }
  else{
    
    
    if(String(readS) != "OFFLINE"){
         sendChar('r'); //get roll
      for(int i=0; i<20; i++){
        pitch[i] = readS[i];
        readS[i] = '\0';
      }
      
      readStringRF(readS, timeout);

      if(String(readS) == "OFFLINE"){
        EsploraTFT.stroke(255,0,0);
        EsploraTFT.text(readS, 60, 90);
        EsploraTFT.stroke(255,255,255);
      }
      else{
        for(int i=0; i<20; i++){
          roll[i] = readS[i];
        }
        EsploraTFT.text("P: ", 60, 90);
        if(!clearScreen){
          EsploraTFT.stroke(0,0,0);
          EsploraTFT.fill(0,0,0);
          EsploraTFT.rect(70, 90, 25, 15);
          EsploraTFT.stroke(255,255,255);
        }
        EsploraTFT.text(pitch, 73, 90);
        EsploraTFT.text("R: ", 100, 90);
        if(!clearScreen){
          EsploraTFT.stroke(0,0,0);
          EsploraTFT.fill(0,0,0);
          EsploraTFT.rect(110, 90, 25, 15);
          EsploraTFT.stroke(255,255,255);
        }
        EsploraTFT.text(roll, 113, 90);
        
      }
      
    }
    else{
      EsploraTFT.stroke(255,0,0);
      EsploraTFT.text(readS, 60, 90);
      EsploraTFT.stroke(255,255,255);
    }
  }
}
void checkSensorMenu(){
    int button = Esplora.readJoystickSwitch();
  if(button == LOW){
    setCurrentMenu(0);
    setupStartMenu();
  }
  else  
    setupSensorMenu(false);
}
