void setup() {
  pinMode(A0, INPUT); // Read in the 10-bit "analog" signal from pin A0
  pinMode(10, OUTPUT); // Setup pins 10-13 as output pins
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600); // Setup outputting to the serial output. For our purposes, "9600" is just a magic number
}

bool decode(int x, int k) {
  return (x & (1 << k)) != 0;
}

void loop() {
  int s = analogRead(A0); // Read the singal on pin A0
  Serial.println(s); // Output that signal to the serial output
  digitalWrite(10, decode(s, 6) ? HIGH : LOW); // Decode the 7th bit
  digitalWrite(11, decode(s, 7) ? HIGH : LOW);
  digitalWrite(12, decode(s, 8) ? HIGH : LOW);
  digitalWrite(13, decode(s, 9) ? HIGH : LOW); // Decode the 10th bit
  delay(10);
}
