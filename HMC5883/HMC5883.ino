#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;

int error = 0;

void setup(){
  Serial.begin(9600);
  compass = HMC5883L(); // Construct a new HMC5883 compass.

  error = compass.SetScale(1.3); // Set the scale of the compass.
  if(error != 0) Serial.println(compass.GetErrorText(error));
  
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) Serial.println(compass.GetErrorText(error));
}

void loop(){
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  float heading = atan2(scaled.YAxis, scaled.XAxis);
  
  float declinationAngle = (607*PI)/10800;
  heading += declinationAngle;
  
  if(heading < 0) heading += 2*PI;
  if(heading > 2*PI) heading -= 2*PI;
  
  heading *= 180/M_PI; // To deg

  Output(scaled, heading);
}

void Output(MagnetometerScaled scaled, float heading) {
   Serial.print(scaled.XAxis);
   Serial.print("\t");   
   Serial.print(scaled.YAxis);
   Serial.print("\t");   
   Serial.print(scaled.ZAxis);

  // Serial.print(" (");Serial.print(heading);Serial.print(")");
   
   Serial.println();
}
