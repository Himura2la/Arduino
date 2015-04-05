#include <MMA7455.h>
#include <Wire.h>

MMA7455 mySensor = MMA7455();

char xVal, yVal, zVal;
float x, y, z;

void setup() {
  Serial.begin(9600);
  mySensor.initSensitivity(2); // 2 = 2g, 4 = 4g, 8 = 8g
}

void loop() {
  xVal = mySensor.readAxis('x');
  yVal = mySensor.readAxis('y');
  zVal = mySensor.readAxis('z');
  
  x = ((float)xVal + 00) / 64;
  y = ((float)yVal + 12) / 64;
  z = ((float)zVal - 12) / 64;
  
  Serial.print(x, 4); Serial.print("\t");
  Serial.print(y, 4); Serial.print("\t");
  Serial.println(z, 4);
}
