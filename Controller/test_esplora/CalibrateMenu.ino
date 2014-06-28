int currentSpeed; //current speed of motors
int stepVar; //increase by stepVar
String buff = "";
char charBuff[10];
void setupCalibrateMenu(){
  sendChar('c');
  char c = readCharTimeout(timeout);
  if(c == 'a') //acknowledge
  {
    stepVar = 1;
    currentSpeed = 1000;
    EsploraTFT.background(0,0,0); //clear screen
    createButton(EsploraTFT.width() - 50, EsploraTFT.height() - 30, 40, 20, "Back", 1, 0);
    EsploraTFT.textSize(1);
    EsploraTFT.text("Switch 3 -> speed += step", 5, 5);
    EsploraTFT.text("Switch 1 -> speed -= step", 5, 20);
    EsploraTFT.text("Switch 4 -> step++", 5, 35);
    EsploraTFT.text("Switch 2 -> step--", 5, 50);
    EsploraTFT.text("Current speed: ", 5, 75);
    EsploraTFT.text("Current step: ", 5, 90);
    paintSpeed();
    paintStep();
  }
  else{
    EsploraTFT.background(0,0,0);
    EsploraTFT.stroke(255,0,0);
    EsploraTFT.textSize(1.6);
    EsploraTFT.text("COMMUNICATION DOWN!", 15, 50);
    createButton(EsploraTFT.width() - 50, EsploraTFT.height() - 30, 40, 20, "Back", 1, 0);
    EsploraTFT.textSize(1);
    EsploraTFT.stroke(255,255,255);
  }

}

void paintSpeed(){
  buff = "";
  buff = String(currentSpeed);
  buff.toCharArray(charBuff, 10);
  EsploraTFT.fill(0,0,0);
  EsploraTFT.stroke(0,0,0);
  EsploraTFT.rect(90,75, 30, 12);
  EsploraTFT.stroke(0,255,0);
  EsploraTFT.text(charBuff, 90, 75);
  EsploraTFT.stroke(255,255,255);
  for(int i=0;i<10;i++){
    charBuff[i] = '\0';
  }
}

void paintStep(){
  buff = "";
  buff = String(stepVar);
  buff.toCharArray(charBuff, 10);
  EsploraTFT.fill(0,0,0);
  EsploraTFT.stroke(0,0,0);
  EsploraTFT.rect(85,90, 25, 12);
  EsploraTFT.stroke(0,255,0);
  EsploraTFT.text(charBuff, 85, 90);
  EsploraTFT.stroke(255,255,255);
  for(int i=0;i<10;i++){
    charBuff[i] = '\0';
  }
}
  

void updateVars(int button){
  switch(button){
    case SWITCH_1:
      if(currentSpeed - stepVar > 0)
        currentSpeed-=stepVar;
        RFSerial.println(String(currentSpeed));
        sendChar('!');
      paintSpeed();
      delay(10);
    break;
    case SWITCH_2: 
      if(stepVar>0)
        stepVar--;
      paintStep();
    break;
    case SWITCH_3: 
      currentSpeed+=stepVar;
      RFSerial.println(String(currentSpeed));
      sendChar('!');
      paintSpeed();
      delay(10);
    break;
    case SWITCH_4: 
      stepVar++;
      paintStep();
    break;
    default:
    break;
  }
}

void checkCalibrateMenu(){
  int yButton = Esplora.readJoystickSwitch();
  if(Esplora.readButton(SWITCH_1) == LOW){
    updateVars(SWITCH_1);
  }
  if(Esplora.readButton(SWITCH_2) == LOW){
    updateVars(SWITCH_2);
  }
  if(Esplora.readButton(SWITCH_3) == LOW){
    updateVars(SWITCH_3);
  }
  if(Esplora.readButton(SWITCH_4) == LOW){
    updateVars(SWITCH_4);
  }

  
  
  
  if(yButton == LOW){
    RFSerial.println("BACK!");
    setCurrentMenu(0);
    setupStartMenu();
  }
}
