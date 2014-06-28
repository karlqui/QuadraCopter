

int timeout = 2000;
char readS[20];
#include "Esplora.h"  
#include "TFT.h"
#include "SPI.h"
#include <SoftwareSerial.h>
 SoftwareSerial RFSerial(11, 3);
//#DEFINE DEBUG
//#DEFINE PRINT_RF



char curString[20];
void setup() {
  // put your setup code here, to run once:
    EsploraTFT.begin();
    EsploraTFT.background(0,0,0);
    Serial.begin(9600);
    setupRFSerial();
    EsploraTFT.stroke(255,255,255);
  // static text
  EsploraTFT.text("Received char",0,0);
  
  setupStartMenu();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(charAvail()){ 
    
  
  }
  else if(Serial.available()){
      /*char c = Serial.read();
      mySerial.write(c);*/
  }
  checkMenu();
}
