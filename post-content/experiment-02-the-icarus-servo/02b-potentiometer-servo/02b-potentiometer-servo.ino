#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(9); // Servo output
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(A0); // Potentiometer input
  int out = map(val, 0, 1023, 0, 180);
  servo.write(out); // Write to the servo output

  Serial.println(val);
  delay(15);
}
