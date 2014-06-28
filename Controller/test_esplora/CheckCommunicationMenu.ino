void checkCommunicationMenu(){
  int button = Esplora.readJoystickSwitch();
  
  if(button == LOW){
    setCurrentMenu(0);
    setupStartMenu();
  }   
  
}

void setupCommunicationMenu(){
  EsploraTFT.background(0,0,0);
  createButton(EsploraTFT.width() - 50, EsploraTFT.height() - 30, 40, 20, "Back", 1, 0);
  EsploraTFT.textSize(1.2);
  EsploraTFT.text("Sending: E", 10, 30);
  sendChar('E');
  EsploraTFT.text("Received: ", 10, 60);

        delay(10);
  char c = readCharTimeout(timeout);
  delay(10);
  char temp[2] = "";
  temp[0] = c;
  EsploraTFT.text(temp, 70, 60); //@TODO RÖD FÄRG
      
      if(c == 'E'){  //using '!' as terminating string symbol
    EsploraTFT.stroke(0,255,0);
    EsploraTFT.text("COMMUNICATION UP!!", 10, 90); 
     EsploraTFT.stroke(255,255,255);
  }
  else{
    EsploraTFT.stroke(255,0,0);
    EsploraTFT.text("NO COMMUNICATION!!", 10, 90);
     EsploraTFT.stroke(255,255,255);
  }
}
