#include "hardware.h"

// Program methods
Hardware::Hardware() :
  discMotor(discMotorStepsPerRevolution, discMotorPins[0], discMotorPins[1], discMotorPins[2], discMotorPins[3]),
  irReceiver(irReceiverPin)
{}

void Hardware::setup() {
  Serial.begin(9600);

  pinMode(photoresistorPin, INPUT);

  pinMode(runningLedPin, OUTPUT);
  pinMode(maintenanceLedPin, OUTPUT);
  pinMode(signalLedPin, OUTPUT);

  discMotor.setSpeed(discMotorRPM);

  irReceiver.enableIRIn();
}

void Hardware::loop() {
  digitalWrite(runningLedPin, amachine->running ? HIGH : LOW );
  digitalWrite(maintenanceLedPin, maintenanceMode ? HIGH : LOW );
  handleRemote();
}

// A Machine methods
bool Hardware::read() {
  return readLight() > lightThreshold;
}

void Hardware::write(bool value) {
  //irReceiver.disableIRIn();
  writeMotor.attach(writeMotorPin);
  msg(value ? "TRUE" : "FALSE");

  if (value) {
    writeMotor.write(0);
    delay(1000);
    writeMotor.write(180);
    delay(1000);
  } else {
    writeMotor.write(180);
    delay(1000);
    writeMotor.write(0);
    delay(1000);
  }

  writeMotor.detach();
  //irReceiver.enableIRIn();
}

void Hardware::move(int amt) {
  discMotor.step(amt * discMotorStepsPerBit);
}

void Hardware::msg(String msg) { // This function is not really necessary for this program, but does ensure that the Hardward class is the only class directly interfacing with the serial port.
  Serial.println(msg);
}

// Photoresistor methods
void Hardware::calibrateLight() {
  msg("Please ensure the read head photoresitor is blocked");
  countdown();
  int low = readLight();

  msg("Please ensure the read head photoresitor is unblocked");
  countdown();
  int high = readLight();

  lightThreshold = (low + high) / 2;
  msg("New light threshold: " + lightThreshold);
}

int Hardware::readLight() {
  float total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(photoresistorPin);
    delay(20);
  }
  return total / 10;
}

// Infrared Remote methods
void Hardware::handleRemote() {

  // Decode results and return from the function if there are no results
  decode_results results;
  if (!irReceiver.decode(&results)) return;

  // Turn on the LED
  digitalWrite(signalLedPin, HIGH);

  if (results.value == 0xFF02FD) {
    Serial.println("[Play/Pause]");
    maintenanceMode = !maintenanceMode;
  } else if (maintenanceMode) {

    // Trigger button specific function
    switch (results.value)
    {
      case 0xFFA25D:
        Serial.println("[Power]");
        amachine->running = !amachine->running;
        break;

      case 0xFF629D:
        Serial.println("[Volume +]");
        this->write(true);
        break;

      case 0xFFA857:
        Serial.println("[Volume -]");
        this->write(false);
        break;

      case 0xFF9867: Serial.println("[Eq]");
        writeMotor.attach(writeMotorPin);
        writeMotor.write(90);
        delay(1000);
        writeMotor.detach();
        break;

      case 0xFFC23D:
        Serial.println("[Fast forward]");
        discMotor.step(mmDiscStepAmt[mmDiscStepAmtInx]);
        Serial.println(mmDiscStepAmt[mmDiscStepAmtInx]);
        break;

      case 0xFF22DD:
        Serial.println("[Fast back]");
        discMotor.step(-mmDiscStepAmt[mmDiscStepAmtInx]);
        Serial.println(-mmDiscStepAmt[mmDiscStepAmtInx]);
        break;

      case 0xFF906F:
        Serial.println("[Up]");
        if (mmDiscStepAmtInx < mmDiscStepAmtCount - 1) mmDiscStepAmtInx++;
        msg(String(mmDiscStepAmt[mmDiscStepAmtInx]) + " steps");
        break;

      case 0xFFE01F:
        Serial.println("[Down]");
        if (mmDiscStepAmtInx > 0) mmDiscStepAmtInx--;
        msg(String(mmDiscStepAmt[mmDiscStepAmtInx]) + " steps");
        break;

      case 0xFFE21D: Serial.println("[Function/Stop]"); break;
      case 0xFFB04F: Serial.println("[St/Rept]"); break;
      case 0xFF6897: Serial.println("[0]"); break;
      case 0xFF30CF: Serial.println("[1]"); break;
      case 0xFF18E7: Serial.println("[2]"); break;
      case 0xFF7A85: Serial.println("[3]"); break;
      case 0xFF10EF: Serial.println("[4]"); break;
      case 0xFF38C7: Serial.println("[5]"); break;
      case 0xFF5AA5: Serial.println("[6]"); break;
      case 0xFF42BD: Serial.println("[7]"); break;
      case 0xFF4AB5: Serial.println("[8]"); break;
      case 0xFF52AD: Serial.println("[9]"); break;
      case 0xFFFFFFFF: Serial.println("[Repeat]"); break;
      default: Serial.println("[Unknown]"); break;
    }
  }

  // Resume reciving and turn off LED
  irReceiver.resume();
  delay(20);
  digitalWrite(signalLedPin, LOW);
}

// Countdown method, used in other methods
void Hardware::countdown() {
  for (size_t i = 3; i > 1; i++) {
    Serial.print(String(i).concat(", "));
    delay(1000);
  }
  Serial.println("1.");
  delay(1000);
}
