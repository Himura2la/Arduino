#include <OneWire.h>
OneWire ds(8);
 
int i;
byte data[9];
byte addr[8] = {0x28, 0xFF, 0x26, 0x34, 0x64, 0x14, 0x3, 0x64};

void setup() {
  Serial.begin(9600);

/*  === Get device address ===
  byte addr[8];
  while (ds.search(addr)) {
    Serial.print("byte addr[8] = {");
    for(i = 0; i < 8; i++) {
      if (i) Serial.print(", ");
      Serial.print("0x");
      Serial.print(addr[i], HEX);
    }
    Serial.println("};");
  }
  ds.reset_search();
  delay(250);//*/
}


void loop() {
  ds.reset(); 
  ds.select(addr);
  ds.write(0x44); // Start conversion
  delay(750);
  
  ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad
  
  for (i = 0; i <= 8; i++)
    data[i] = ds.read();

  if (OneWire::crc8(data, 8) == data[8]){ //Check CRC
    int16_t raw = (data[1] << 8) | data[0];
    byte cfg = data[4] & 0x60;
    switch(cfg) {
      case 0x00: raw &= ~7; break;
      case 0x20: raw &= ~3; break;
      case 0x40: raw &= ~1; break;
    }
    float T = (float)raw / 16.0;
    Serial.print("T = ");
    Serial.println(T);
  }
  else Serial.println("Data corrupt!");
}
