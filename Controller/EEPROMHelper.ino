#include "EEPROM.h"

void saveEEPROM(String paraphrase, int data){ //1024 bytes of EEPROM on the esplora -- Empty possitions have the value of 255

  int i=0;
  String tempPara = "";
  bool paraExists = false; //if the paraphrase already exists
  byte b;
  b = EEPROM.read(i);
  while(b!=255)//Read until empty positions -- Loop through every paraphrase in the mem to check if it already exists
  {

    while((char)b!=':'){//paraphrase
      tempPara += (char)b;
      i++;
      b = EEPROM.read(i);
    }
    if(tempPara==paraphrase){
      paraExists = true; //paraphrase found, stop looking
      break;
    }
    tempPara = "";
    while((char)b!='|'){//loop through data
      i++;
      b = EEPROM.read(i);
    }
    i++;
    b = EEPROM.read(i);
  }
  if(paraExists){//@TODO replace data on index i
    i++;
    byte high = highByte(data);
    EEPROM.write(i, high);
    byte low = lowByte(data);
    i++;
    EEPROM.write(i, low);
  }
  else{ //@TODO add new paraphrase and data on index i
  
    for(int j=0;j<paraphrase.length(); j++){
      EEPROM.write(i, paraphrase[j]);
      i++;
    }
    EEPROM.write(i, ':');
    i++;
    EEPROM.write(i, highByte(data));
    i++;
    EEPROM.write(i, lowByte(data));
    i++;
    EEPROM.write(i, '|');
  }
}

int readEEPROM(String paraphrase){ //read int value from EEPROM
    int i=0;
  String tempPara = "";
  bool paraExists = false; //if the paraphrase already exists
  byte b;
  b = EEPROM.read(i);
  while(b!=255)//Read until empty positions -- Loop through every paraphrase in the mem to check if it already exists
  {

    while((char)b!=':'){//paraphrase
      tempPara += (char)b;
      i++;
      b = EEPROM.read(i);
    }
    if(tempPara==paraphrase){
      paraExists = true; //paraphrase found, stop looking
      break;
    }
    tempPara = "";
    while((char)b!='|'){//loop through data
      i++;
      b = EEPROM.read(i);
    }
    i++;
    b = EEPROM.read(i);
  }
  if(paraExists){//@TODO replace data on index i
    i++;
    byte high = EEPROM.read(i);
    i++;
    byte low = EEPROM.read(i);
  
    return word(high, low);
  }
  else{ //@TODO add new paraphrase and data on index i
    return -1;
  }
}

void cleanEEPROM(){
  for(int i=0;i<1024;i++){
    EEPROM.write(i, 255);
  }
}

void printEEPROM(){
  Serial.println("printing!");
  int i = 0;
  byte b = EEPROM.read(i);
  while(b!=255){
    Serial.println((char)b);
    i++;
    b = EEPROM.read(i);
    
  }
}
