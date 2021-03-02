void setup() {
  pinMode(7, OUTPUT); // LED ouput
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(A0); // Potentiometer input
  int out = map(val, 0, 1023, 0, 255);
  analogWrite(7, out);

  Serial.println(out);
}
