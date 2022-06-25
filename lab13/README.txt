=====================================================================
CS2110                        Lab 15                        Fall 2021
=====================================================================


********** RUN THIS IN THE DOCKER VNC CLIENT (your web browser) **********
(This will NOT work on your local system or using ./cs2110docker.sh -it)

Assignment
----------
For this lab you will be doing two things.

First, you will be implementing drawFullScreenImage using DMA. This function takes in an image and draws it on the
GBA screen, read more in the puppies.c file.

Second, you will be implementing a state machine similar to what you'll likely need for Homework 8.

When you press A (the z key in our emulator), the screen should change to a new image of a puppy.
There's 5 frames and they should loop, i.e,
1->2->3->4->5->1->2..
We've provided the images and you can draw them with your drawFullScreenImage function: 'drawFullScreenImage(puppyX)', where X is the frame number you want to draw.

Two rules:

 1. Holding down A (the "Z" key on your keyboard) MUST NOT quickly cycle through all the states.
 2. Don't add any loops.

Read more instructions in the puppies.c file

When finished, cd into the directory containing puppies.c
and the Makefile. To build and run the emulator, run:

    $ make med

When you are done, you should be able to switch between different puppies by pressing "Z" on your keyboard (this corresponds to the "A" button in the GBA).

