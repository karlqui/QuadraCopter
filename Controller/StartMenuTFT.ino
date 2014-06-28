int currentMenu = 0;

void setupStartMenu(){
  EsploraTFT.background(0,0,0);

  createButton(10, 5, EsploraTFT.width() - 20, 20, "Start", 1, 0);
  createButton(10, 30, EsploraTFT.width() - 20, 20, "Test Communication", 1, 1);
  createButton(10, 55, EsploraTFT.width() - 20, 20, "Test Sensors", 1, 2);
  createButton(10, 80, EsploraTFT.width() - 20, 20, "Calibrate Lift-off", 1, 3);
  createButton(10, 105, EsploraTFT.width() - 20, 20, "Calibrate MPU and save to EEPROM", 1, 4);
  setCurrentButton(0);
}

void checkMenu(){
  
  if(currentMenu == 0)
    checkStartMenu();
  else if(currentMenu == 1)
    checkCommunicationMenu();
  else if(currentMenu == 2)
    checkSensorMenu();
  else if(currentMenu == 3)
    checkCalibrateMenu();
  else if(currentMenu == 4)
    checkCalibrateMPUMenu();
  
  delay(100);
}



void menuAction(int id){
  switch(id){
    case 0:
      //@TODO start quadcopter
      break;
    case 1:
      setupCommunicationMenu();
      currentMenu = 1;
      break;
    case 2:
        setupSensorMenu(true);
      currentMenu = 2;
      break;
    case 3:
        setupCalibrateMenu();
      currentMenu = 3;
      break;
    case 4:
      setupCalibrateMPUMenu();
      currentMenu = 4;
    default:
      break;
  }
}

void checkStartMenu(){
  int xValue = Esplora.readJoystickX();        
  int yValue = Esplora.readJoystickY();        
  int button = Esplora.readJoystickSwitch();   
  
  int x = map(xValue, -512, 512, 10, -10); 
  int y = map(yValue, -512, 512, -10, 10);

  

  if(y > 4){
    if(getCurrentButton() + 1 > 4)
      setCurrentButton(0);
    else
      setCurrentButton(getCurrentButton() + 1);
  }
  else if(y < -4){
    if(getCurrentButton() - 1 < 0)
      setCurrentButton(4);
    else
      setCurrentButton(getCurrentButton() - 1);
  }
  else if(button == LOW){
    
    menuAction(getCurrentButton());
  }
}






void setCurrentMenu(int i){
  currentMenu = i;
}

