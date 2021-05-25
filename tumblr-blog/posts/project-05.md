# Final Project #5 : Bit reading
*Experiment conducted 2021/05/11*

This time I set out to test how I could read which state my cardboard memory cells are in. I tested how well a photoresistor could be used to detect if the cardboard was blocking light to it. In the video below I demonstrate that the photo resistor could do this quite successfully, but also explain the different factors that contribute to how well it will or won't work on the final machine. After this initial experiment, I also ran additional tests with different coloured additional light sources and different lengths of cardboard, to see what affect that had on the photoresistor's outputs.

For this experiment I reused the code and writing from my first photoresistor decoder experiment (modified to my needs.)

# Experimenting with Additional Light Sources
After my initial experiment, I tested putting different colours of LED above the photoresistor (but blockable by the cardboard) to see how that affected the photoresistor's ability to detect the cardboard. I also experimented with different widths of cardboard flaps to see what affect that had.

# Results
Each table shows the output from the photoresistor for each combination of additional light source and width of cardboard. Less light equates to a larger output from the photoresistor.

## Round 1
| Additional light source | No cardboard | 2.1cm cardboard | 6.1cm cardboard |
| ----------------------- | ------------ | --------------- | --------------- |
| Green LED               | 374          | 610 (+236)      | 687 (+313)      |
| Red LED                 | 386          | 616 (+230)      | 694 (+308)      |
| Blue LED                | 448          | 619 (+171)      | 707 (+259)      |
| Yellow LED              | 459          | 616 (+157)      | 686 (+227)      |
| None                    | 544          | 617 (+73)       | 701 (+157)      |

**Ranking 2.1cm:** Green, Red, Blue, Yellow, None  
**Ranking 6.1cm:** Green, Red, Blue, Yellow, None  

## Round 2
| Additional light source | No cardboard | 2.1cm cardboard | 6.1cm cardboard |
| ----------------------- | ------------ | --------------- | --------------- |
| Green LED               | 405          | 627 (+222)      | 699 (+294)      |
| Red LED                 | 392          | 632 (+240)      | 704 (+312)      |
| Blue LED                | 401          | 614 (+213)      | 693 (+292)      |
| Yellow LED              | 492          | 632 (+140)      | 702 (+210)      |
| None                    | 564          | 627 (+63)       | 698 (+134)      |

**Ranking 6.1cm:** Red, Green, Blue, Yellow, None  
**Ranking 2.1cm:** Red, Green, Blue, Yellow, None  
