#include <Servo.h>
#include "IRremote.h"

Servo servo;
IRrecv ir(13);
void setup() {
  servo.attach(6);
  ir.enableIRIn();
}

void loop() {
  
}
