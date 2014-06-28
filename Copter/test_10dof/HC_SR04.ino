int DIST_TRIG = 3;
int DIST_ECHO = 4;
int maximumRange = 2000; // Maximum range needed
int minimumRange = 30; // Minimum range needed
long duration; // Duration used to calculate distance

void setupHC_SR04(){
   pinMode(DIST_TRIG, OUTPUT);
   pinMode(DIST_ECHO, INPUT);
}

void setMaximumRange(int range){
  maximumRange = range;
}

int getMaximumRange(){
  return maximumRange;
}
bool testConnectionHC(){
  updateDistance();
  return distance != -1;
}

void updateDistance(){
  double tempDist;
 digitalWrite(DIST_TRIG, LOW); 
 delayMicroseconds(2); 

 digitalWrite(DIST_TRIG, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(DIST_TRIG, LOW);
 duration = pulseIn(DIST_ECHO, HIGH);
 
 tempDist = duration/5.82; //distance in millimeters
 
 if (distance >= maximumRange || distance <= minimumRange){
 distance = -1;
 
 }
 else {

  distance = tempDist;

 }
 #ifdef PRINT_DISTANCE
  Serial.print("Distance:  ");
  Serial.println(distance);
#endif
}

