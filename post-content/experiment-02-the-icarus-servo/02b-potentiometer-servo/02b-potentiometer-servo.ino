#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(9); // Servo output
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(A0); // Potentiometer input
  int out = map(val, 10, 360, 0, 180);
  servo.write(out);
  Serial.println(val);
  delay(15);
}
