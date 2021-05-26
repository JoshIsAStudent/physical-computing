void setup() {
  pinMode(7, OUTPUT); // LED ouput
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(A0); // Potentiometer input
  int out = map(val, 0, 1023, 0, 255); // Converts the input range of the potentiomiter (0-1023) to the output range of the analog pin (0-255)
  analogWrite(7, out); // Write to the LED output

  Serial.println(out);
  delay(10);
}
