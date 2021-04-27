# Final Project 01

# The Idea
[Charles Babbage's mechanical computer](https://en.wikipedia.org/wiki/Charles_Babbage) and [Alan Turing's a-machine](https://en.wikipedia.org/wiki/Turing_machine) (better known as the Turing Machine) both live rent-free in my imagination, which leads to some esoteric ideas and trains of thought! For my project I want to create a primitive Turing Machine - where the itself machine runs on on the Arudino, which reads and writes to a mechanical memory. For now I'm calling it "The Overengineered Turning Machine", but we might come up with a more flattering name later.

![A mindmap of project ideas that I brainstormed](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/project-01/projects-brainstorm.jpg)
**Fig 1:** I did _try_ to have a more reasonable idea before jumping right into The Overengineered Turning Machine, but this idea was easily the most captivating.

I am reasonably confident in my ability to program the machine itself, the mechanical memory is very much the area of many unknowns. I made my first step was to brainstorm how it may work. Running experiments is the only true way to verify a concept, however I still wanted to take time to explore options on paper to help inform my thinking later on in the process, and if I'm lucky eliminate some dud ideas early on.

# Brainstorming
Modern computers use Random Access Memory, which means that the value at any given memory cell can be accessed as easily and quickly as any other. In the spirit of the hypothetical a-machine however, I want to construct a sequential memory.

It has three functions it needs to be able to achieve.
1. Move the memory cells.
2. Write at least two symbols to the current cell.
3. Read the symbol at the current cell.

![A series of sketches brainstorming how the mechanical memory may work.](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/project-01/memory-brainstorm.jpg)
**Fig 2:** Sketches of how the various read/write mechanisms of the machine could work.

## Moving memory cells
The key insight here was the memory strip does not need to be a literal strip, but can in fact be a loop.

In order to be able to read and write to memory, it seemed very likely that some moving parts would have to exist on the strip (making marks on the strip would be both difficult to sense, and difficult to "undo"). A long, presumably rigid, strip though possible, would potentially require a lot of space on one axis, and may be more difficult to move. A loop memory on the other hand allows the memory to stay in a confined space, and simplifies moving the memory cells to rotating with a motor.

When I start experimenting, the loop could be the circumference of a disk, or possibly a ring. The only drawback of this is that a lot of wasted space exists inside the disk.

## Reading and writing
So long as the memory can read and write at least two "symbols", the machine will be able to operate. The hypothetical a-machine used a strip of paper that could write, erase, and detect symbols. Though the prospect of leaving the binary realm by having more than two symbols is exciting, for practical purposes detecting the absence or presence of an object or blockage may be best.

Looking at the many approaches I brainstormed, it appears there is a tradeoff between the complexity of a memory cell and the complexity of the read write mechanism. The less complex you make one, the more complex becomes the other.

# The plan: Prototype 1

The first experiments I need to perform are:
1. Rotation of the disc/loop
2. Mechanics of the read sensor
3. Mechanics of the write motor
4. All parts together
