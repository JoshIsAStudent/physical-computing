# Experiment 01: Photoresistor Decoder
In this experiment you will take the [10-bit analogue]>[is that the correct term?] output of a photoresistor (a.k.a photocell), decode the 4 most significant bits using code running on the Arduino, then display those four bits on LEDs.

[]>[Include an image/video!]

## [Components]>[Check that these are correct]

@standard-components
* 1 x Photoresistor
* 1 x [X]>[How many??]Ω resistor
* 4 x LEDs
* 4 x [X]>[How many??]Ω resistors

## Step 1: Wiring the photo resistor
Wire your breadboard as shown, using the [X]>[How many??]Ω resistor.

![](photo/temp.png)

[]>[Show a diagram of the first part of the circuit]

Here the red wire is taking a 5V signal from the Arduino into the circuit. It first passes through the [X]>[How many??]Ω resistor, and then through the photoresistor. The resistance of the first resistor is static, however the resistance of the photoresistor changes depending on the light level. The more light, the [more/less]>[which is it?] resistance there is. We then use black wires to ground the signal. Two wires are used, connecting the resistor to the [blue line of the breadboard]>[what is it called?], and the [blue line of the breadboard]>[what is it called?] to the Arduino [ground pin]>[is this what it's called?], as later we'll also ground our LEDs by connecting them to the [blue line of the breadboard]>[what is it called?].

The orange wire is used to carry the [voltage/current]>[which one is it?] into the Arduino. We connect to pin [X]>[which one], as this pin is able to read the analogue value of the [voltage/current]>[which one is it?] as a 10-bit signal. This allows us to read an arbitrary unit numerical value, instead of just whether the signal is high or low.

[You might wonder why two resistors are used?]>[Why does that happen J??]

## Step 2: Decoding the signal in code
By reading the signal carried by the orange wire, we can now read how much light the photocell is detecting. The more light, the [higher/lower]>[??] the signal will be.

We can program our `setup()` function to read this analogue signal into the Arduino. In the meantime, we will also set up pins 10-13 as digital outputs, which we will use to output the 4 most significant bits of the signal.

```C
void setup() {
  pinMode(A0, INPUT); // Read in the 10-bit "analog" signal from pin A0
  pinMode(10, OUTPUT); // Setup pins 10-13 as output pins
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600); // Setup outputting to the serial output. For our purposes, "9600" is just a magic number
}
```

Next we will create a function that will take that signal as input, and output the value of a particular bit as a boolean. Here `x` is the value being decoded and `k` is which bit we are decoding (0-indexed).

```C
bool decode(int x, int k) {
  return (x & ( 1 << k )) != 0;
}
```

[We now have everything we need to create our loop function]>[Is it really worth me explaining this more??].

```C
void loop() {
  int s = analogRead(A0); // Read the singal on pin A0
  Serial.println(s); // Output that signal to the serial output
  digitalWrite(10, decode(s, 6) ? HIGH : LOW); // Decode the 7th bit
  digitalWrite(11, decode(s, 7) ? HIGH : LOW);
  digitalWrite(12, decode(s, 8) ? HIGH : LOW);
  digitalWrite(13, decode(s, 9) ? HIGH : LOW); // Decode the 10th bit
  delay(10);
}
```

@complete-code

## Step 3: Displaying the decoded signal
Now that our code is decoding the signal, we want to display that using our four LEDs. Each LED has it's own [X]>[How many??]Ω resistor. They are wired the same, except that they each connect to a different pin on the Arduino. As we want the left-most LED to display the most significant bit (the 10th bit), we will connect it to pin 13.

[]>[Show a diagram!]

## [There you have it!]>[Figure out what evaluation to include in here!]


# [Checklist]>[Remove this once done]
* a description of the experiment(s)
plenty of photos and videos documenting the experiment(s)
* technical information, including code and circuit diagrams
* a list of the components used
* links to any outside sources of information used in the experiment(s)
* a record of any troubleshooting required: what went wrong, and how did you overcome it?
* an evaluation: what was learned, how could it be improved, how could it be used?
