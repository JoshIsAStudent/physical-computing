# Experiment #1 : Photoresistor to Binary Decoder
*Experiment conducted 2021/02/23*

For my first experiment, I wired the Arduino to read the analog output of a potential divider circuit with a photoresistor in it (a.k.a. a photocell) as a 10-bit value. It then decoded the 4 most significant bits in code and displayed those 4 bits on LEDs.

?[youtube-video](wad_VNBkfw0)

## Components Used
?[standard-components]
* 1 x Photoresistor
* 1 x 5KΩ resistor
* 4 x LEDs
* 4 x 220Ω resistors

## Step 1: Wiring The Photoresistor
I first wired the photoresistor as shown below, using the 5KΩ resistor.

![](photoresistor-diagram.png)

A red wire takes a 5V voltage from the Arduino into the circuit. The voltage passes through the 5KΩ resistor, which then goes through the photoresistor. The black wires then carry the voltage through to the ground pin of the Arduino. The two resistors wired in this way creates a potential divider circuit. I've deliberately used two black wires to ground the signal, one connecting the potential divider to the negative rail, and one connecting the negative rail to the Arduino. This will make it easy to ground the LEDs later by connecting them to the negative rail.

The resistance of the first resistor is static, however the resistance of the photoresistor changes depending on the light level. The more light, the less resistance there is. This means that the more light there is, the lower the signal from the potential divider will be.

The orange wire is used to carry the signal from the potential divider into the Arduino. We connect to pin A0, as the analog pins connect to analog to digital converters. These allow us to read the analog singal from the circuit as a 10-bit, arbitrary unit, numerical value. If we used a digital pin instead, it would only be able to read if the value was high or low.

## Step 2: Decoding The Signal in Code
By reading the signal carried by the orange wire, we can now read how much light the photoresistor is detecting. The more light, the smaller the signal will be.

We can program our `setup()` function to read this analog signal into the Arduino. In the meantime, we will also set up pins 10-13 as digital outputs, which we will use to output the 4 most significant bits of the signal to the LEDs.

```cpp
void setup() {
  pinMode(A0, INPUT); // Read in the 10-bit "analog" signal from pin A0
  pinMode(10, OUTPUT); // Setup pins 10-13 as output pins
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600); // Setup outputting to the serial output. For our purposes, "9600" is just a magic number
}
```

Next we will create a function that takes that signal as input, and outputs the value of a particular bit as a boolean. Here `x` is the value being decoded and `k` is which bit we are decoding (0-indexed). (Though it might be slightly erroneous to make this it's own function, it makes the loop code more readable, and the compiler will likely inline the function for us anyway.)

```cpp
bool decode(int x, int k) {
  return (x & ( 1 << k )) != 0;
}
```

We now have everything we need to create our loop function. Here we store the signal from the potential divider in variable `s`, output that value to the serial port, and then one by one decode each bit and update our digital outputs accordingly.

```cpp
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

[You can see the complete code on GitHub.](https://github.com/JoshIsAStudent/physical-computing/blob/main/post-content/experiment-01-photoresistor-decoder/01-photoresistor-decoder/01-photoresistor-decoder.ino).

## Step 3: Displaying The Decoded Signal
Now that our code is decoding the signal and outputting the 4 bits, we want to display that using our four LEDs. Each LED has it's own 220Ω resistor. They are wired in parallel and each in the same way, except that each connects to a different pin on the Arduino. As we want the left-most LED to display the most significant bit (the 10th bit), we will connect it to pin 13.

![](leds-diagram.png)

Depending on what colour and make LEDs you use, you may need to tweak what strength of the LED resistors to achieve the desired brightness

## There you have it!

![](final-circuit-photo.jpg)

This was a fun first experiment into working with electronic components, which went smoothly enough I'm a little suspicious. Though, I did have to experiment with using different strengths of resistor to achieve the desired results with the LEDs and potential divider. Through experimentation in [TinkerCAD](tinkercad.com), I also came to realise the amount of light received by the photoresistor and the output of the potential divider were not linearly correlated. As the amount of light increased, the signal would first decrease slowly, then start decreasing faster and faster. For this experiment that wasn't a problem, but it did mean it was much easier to deliberately create binary numbers 0-3 than 4-7 using the LEDs. This could be resolved in code by converting the non-linear input of the potential divider into a linear one.
