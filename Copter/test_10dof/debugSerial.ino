
void setupDebugSerial(){
    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately
}  

#ifdef DEBUG


void printDebugMessage(String s){
    Serial.println(s);
}
#endif



#ifndef DEBUG // dont do anything unless DEBUG is defined

void printDebugMessage(String s){
}

#endif
