# Final Project #4 : Disc based memory
*Experiment conducted 2021/05/11*

In this experiment created a spinning disc using a plastic sweet tub lid, and tested to see how well I could spin it around using a stepper motor. In the video below, I show the working experiment and explain some of the details as to why it works. (In the video, I also mistakenly refer to the stepper motor as a servo motor!)

?[youtube-video](ginvQo4ddFo)


## The Code & Wiring
The program I used was the `stepper_oneRevolution` program from the Arduino IDE examples (`File > Examples > Stepper > stepper_oneRevolution`). I modified the `stepsPerRevolution` variable to `2048` and the speed parameter in `myStepper.setSpeed` to `15`.

The driver board is used so that the Arduino can more easily control the stepper motor. The stepper motor itself is wired into the driver board, and the driver board into the Arduino. The order of the wires from the Arduino to the driver board is important. In this case, I have wired them to work with the example program.
