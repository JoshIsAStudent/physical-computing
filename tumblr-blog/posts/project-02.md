# Final Project #2 : Ring Based Memory
*Experiment conducted 2021/05/04*

<iframe width="560" height="315" src="https://www.youtube.com/embed/DS2I1JDmLDw" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

[Can't see the video? Watch it on YouTube!](https://youtu.be/DS2I1JDmLDw)

My first experiment was to see if I could create a ring version of the loop memory, able to spin around a centre. I wanted to see if I could create a ring instead of a disc as if I could, then it would be possible to put the read and write heads in the same position, with one positioned inside the ring, and one on the outside (so long as the motor drove the loop from the outside). The weight reduction, though not required, felt like it could be a nice bonus. As is evident from the video however, it was not successful.

# Making The Ring
![A photo of the metal ring laid on a desk.](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/project-02/complete-ring.jpg)

I made the ring out of metal wire, malleable enough to be bent into shape by force, but strong enough to retain it's shape otherwise.

To complete the loop, I wrapped the two ends around each other, and compressed the ends together using plyers. When that proved too difficult, I laid the ring on a chopping board, and hammered the join instead. I had to hit it on four different sides to make the join completely rigid. Shown below are the before and after. Though the join doesn't look particularly compacted in the second image, it was sturdy enough to keep the ring from wobbling.

![A side by side comparison of where the two ends of the wire join. On one side the join has not been compressed, on the other it has.](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/project-02/ring-join-comparison.jpg)

The wheels shown in the video were taken from a dresser. My intention was to attach the wheels to the side of a cylinder - in this case the sides of a plastic sweets tub - and have the ring ride, not along the wheels themselves, but along the flat surface in between them.

![A photo of the ring, placed on top of the wheels attached to the side of the tub.](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/project-02/ring-on-rails.jpg)

# The Issues
As seen in the video, the ring doesn't roll around the wheels. However, the issues run deeper than that. Part of the reason it doesn't roll is it was difficult to get the ring in a circular enough shape just by hand, i.e. without proper tools or a correctly shaped object to wrap it around. Less evident from the video however is that the sides of the tub are actually at a slight angle, ultimately meaning the flat area of the wheel is not perpendicular to gravity. Furthermore, the region was too wide to reasonably keep the ring on one track.

It's become clear from this experiment that to find a way to make this kind of ring roll clearly, let alone also be side driven by a motor and able to hold memory cells, isn't really feasible for this project. My next experiment is to see if I can get a working memory cell and writing mechanism, but after that I will experiment with a disc version of the memory loop.
