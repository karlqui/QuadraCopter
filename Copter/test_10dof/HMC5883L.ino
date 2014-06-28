#include "HMC5883L.h"

// this device only supports one I2C address (0x1E)
HMC5883L mag;

int16_t mx, my, mz;


void setupHMC5883L(){
    mag.initialize();
    mpuBypass(true);
    printDebugMessage(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");
}
bool testConnectionHMC(){
    return mag.testConnection();
}

void updateHeading(){
    mag.getHeading(&mx, &my, &mz);

// To calculate heading in degrees. 0 degree indicates North
    float temp = atan2(my, mx);
    if(temp < 0)
      temp += 2 * M_PI;
    
    heading = temp * 180/M_PI;
#ifdef PRINT_HEADING
    Serial.print("Heading:  ");
    Serial.println(heading);
#endif
  
}
