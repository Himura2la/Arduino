#include <VirtualWire.h>
 
int RF_TX_PIN = 2;

void setup(){
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(4000);
}
 
int i = 0;
void loop() {
  const char *msg = "I cal fly!!!";

  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();

  delay(200);
}
