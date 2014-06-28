#include <Servo.h>

Servo motorX1, motorX2, motorY1, motorY2;
int X1Speed, X2Speed, Y1Speed, Y2Speed = 0;



void setupMotors(){
  motorX1.attach(6); //X positive angle	
  motorY1.attach(9); //Y positive angle
  motorX2.attach(10); //X negative angle
  motorY2.attach(11); //Y negative angle
  delay(50);
  motorX1.write(10); //Initiate motors
  motorX2.write(10);
  motorY1.write(10);
  motorY2.write(10);
  delay(2000);
}

void setSpeed(int speed){ //set speed of all motors

}

void incrSpeed(int val){//@TODO
  
}

void decrSpeed(int val){

}

void rollLeft(){

}

void rollRight(){

}

void pitchForward(){

}

void pitchBackwards(){

}

void rotateRight(int angle){ 
  
}

void rotateLeft(int angle){

}
