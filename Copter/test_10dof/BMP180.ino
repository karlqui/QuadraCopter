#include "BMP085.h"

BMP085 barometer;

int32_t lastMicros;

void setupBMP180() {
  
    barometer.initialize();
    printDebugMessage(barometer.testConnection() ? "BMP085 connection successful" : "BMP085 connection failed");

}
void updateTemperature(){
      barometer.setControl(BMP085_MODE_TEMPERATURE);
    
    // wait appropriate time for conversion (4.5ms delay)
    lastMicros = micros();
    while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds());

    // read calibrated temperature value in degrees Celsius
    temperature = barometer.getTemperatureC();
}

bool testConnectionBMP(){
  return barometer.testConnection();
}


void updateAltitude() {
    float tempPressure;
    
    // request pressure (3x oversampling mode, high detail, 23.5ms delay)
    barometer.setControl(BMP085_MODE_PRESSURE_3); //@TODO NEED TO UPDATE SENSOR READING METHOD... TOO SLOW
    lastMicros = micros();
    while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds());

    // read calibrated pressure value in Pascals (Pa)
    tempPressure = barometer.getPressure();
    
    altitude = barometer.getAltitude(tempPressure, 101230);//air pressure sthlm sea level
    
#ifdef PRINT_ALTITUDE
    Serial.print("Altitude:  ");
    Serial.println(altitude);
#endif
    
}
