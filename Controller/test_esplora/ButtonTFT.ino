#include "Esplora.h"
#include "TFT.h"
#include "SPI.h"
int currentButton = 0;


struct button{
  int x;
  int y;
  int width;
  int height;
  char * text;
  int textSize;
}b[6];


void createButton(int x, int y, int width, int height, char * text, int textSize, int id){
  b[id].x = x;
  b[id].y = y;
  b[id].width = width;
  b[id].height = height;
  b[id].text = text;
  b[id].textSize = textSize;
  
  EsploraTFT.stroke(255,255,255);

  // set the fill color to grey
  EsploraTFT.fill(100,100,100);
  EsploraTFT.rect(x, y, width, height);
  EsploraTFT.textSize(textSize);
  EsploraTFT.text(text, x + 5, y + 5);
}
int getCurrentButton(){
  return currentButton;
}

void setCurrentButton(int id){
  
  EsploraTFT.stroke(255,255,255);
  EsploraTFT.fill(180,180,180);
  EsploraTFT.rect(b[id].x, b[id].y, b[id].width, b[id].height);
  EsploraTFT.textSize(b[id].textSize);
  EsploraTFT.text(b[id].text, b[id].x + 5, b[id].y + 5);
  if(id != currentButton){
    EsploraTFT.stroke(255,255,255); //reset old currentButton
    EsploraTFT.fill(100,100,100);
    EsploraTFT.rect(b[currentButton].x, b[currentButton].y, b[currentButton].width, b[currentButton].height);
    EsploraTFT.textSize(b[currentButton].textSize);
    EsploraTFT.text(b[currentButton].text, b[currentButton].x + 5, b[currentButton].y + 5);
    currentButton = id;
  }
  
  
}
