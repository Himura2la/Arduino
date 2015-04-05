/* SFE_TSL2561 
!!! 3V3 !!!
SDA -> A4
SCL -> A5

For more information see the hookup guide at: 
*/

#include <SFE_TSL2561.h>
#include <Wire.h>

SFE_TSL2561 light;

boolean gain = 0; //0 = X1, 1 = X16;

// If time = 0, integration will be 13.7ms
// If time = 1, integration will be 101ms
// If time = 2, integration will be 402ms
// If time = 3, use manual start / stop to perform your own integration
unsigned char time = 1;
unsigned int ms;  // Integration ("shutter") time in milliseconds

void setup() {
  Serial.begin(9600);
  light.begin();

  light.setTiming(gain, time, ms);
  light.setPowerUp();
}

void loop() {
  delay(ms);
  
  unsigned int data0, data1;
  if (light.getData(data0, data1)) {
    double lux;    // Resulting lux value
    if (light.getLux(gain, ms, data0, data1, lux))
      Serial.println(lux);
    else {
      Serial.print(lux);
      Serial.println(" [Over range]");
    }
  }
  else { // getData() returned false because of an I2C error, inform the user.
    byte error = light.getError();
    printError(error);
  }
}



void printError(byte error) {
  Serial.print("[ERROR ");
  Serial.print(error, DEC);
  Serial.print("]");
  switch(error) {
    case 0: Serial.println("success"); break;
    case 1: Serial.println("data too long for transmit buffer"); break;
    case 2: Serial.println("received NACK on address (disconnected?)"); break;
    case 3: Serial.println("received NACK on data"); break;
    case 4: Serial.println("other error"); break;
    default: Serial.println("unknown error");
  }
}

