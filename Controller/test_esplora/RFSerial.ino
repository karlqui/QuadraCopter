
 

 
 void setupRFSerial(){
   RFSerial.begin(9600);
 }
 
 void flushRF(){
   while(charAvail())
     readCharRF();
 }
 
 bool charAvail(){
   return RFSerial.available();
 }
 void sendChar(char c){
   RFSerial.print(c);
 }

 char readCharRF(){
   return RFSerial.read();
  
 }
 
 char readCharTimeout(int timeout){
   int time = 0;
   while(time < timeout){
     if(charAvail()){
       return readCharRF();
     }
     time++;
     delay(1);
   }
   return -1;
 }
 
void readStringRF(char (&readS)[20],int timeOutDelay){
    int time = 0, i = 0;

    while(1){
      
      if(charAvail()){
        char c = readCharRF();
        Serial.println(c);
        readS[i] = c;
        
        if(c == '!'){
          readS[i] = '\0';
          return;
          
          }
        i++;
      }
      time++;
      
      if(time >= timeOutDelay){
         readS[0] = 'E';
         readS[1] = 'R';
         readS[2] = 'R';
         readS[3] = 'O';
         readS[4] = 'R';
         
         return;
       }
      
      delay(1);
    }
    
    
    
 }
