// Include the libraries we will need. These libraries handle some of the complex parts of controlling the eltronics for us, so we don't have to!
#include <Servo.h>
#include <Stepper.h>
class AMachine // Forward declaration of Hardware class so that we can create a pointer to it. If we included it instead, `machine.h` and `hardware.h` would have cyclic include dependicies

// Hardware
// This class controls all of the Arduino hardware and electronics. This includes that used by the A-Machine, as well as that used for maintenance mode.
class Hardware {
  public:
    // Settings - Input pins
    const uint8_t photoresistorPin = A0;

    // Settings - Output pins
    const uint8_t maintenanceLedPin = 4;
    const uint8_t runningLedPin = 3;
    const uint8_t signalLedPin = 2;
    const uint8_t writeMotorPin = 5;
    const uint8_t irReceiverPin = 6;
    const uint8_t discMotorPins[] = {8, 10, 9, 11};

    // Settings - Motors
    const float discMotorRPM = 16;
    const int discMotorStepsPerRevolution = 2048;
    const int discMotorStepsPerBit = 4;

    // Interfaces
    Stepper discMotor;
    Servo writeMotor;
    AMachine* amachine;

    // Variables
    int lightThreshold = 1024 / 2;
    bool maintenanceMode = true;

    // Program methods
    void setup();
    void loop();

    // A Machine methods
    bool read();
    void write(bool value);
    void move(int amt);
    void msg(String msg);

    // Photoresistor methods
    void calibrateLight();
    int readLight() ;

    // Countdown method, used in other methods
    void countdown();
};
