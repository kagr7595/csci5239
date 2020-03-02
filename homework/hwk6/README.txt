HW06:  Android
Kathy Grimes
CSCI 5239
Based off of Hello GL2 jni example triangle and CSCI 5239 EX10
Also used many web resources including:
https://stackoverflow.com/questions/10961746/opengl-normal-matrix

HW Requirements:
Create a program that allows a scene to be viewed in 3D from any direction
under user control that can be run on the iPhone/iPod/iPad or Android.

You must build some solid 3D objects yourself using OpenGL ES.  In particular,
there are a number of frameworks such as GLKit on the iPhone that permits you
to write applications without using OpenGL ES.  In this assignment I would like
you to get some exposure to the nuts and bolts of OpenGL ES, so using such
frameworks is prohibited.

You may want to start with my simple application and explore features such as
lighting and textures, gestures, and so on.  However, you do NOT have to follow
my example (borrowed from Rideout's iPone 3D programming) and develop the core
code in C++ and only providing a native wrapper.  If you have a good reason to
do so, you may stick with Objective C on the iPhone or Java on the Android
throughout your program.

This is potentially a difficult assignment since you need to install the Xcode
environment for the iPhone or the Android SDK/NDK.  Therefore you may work in
pairs for this assignment with somebody a bit further along on the curve.  Your
README should clearly tell me what the contribution of each team member was.

When you submit the assignment, the person whose environment you used should
upload the project.  Look at my examples on how to clean out stuff I don't
need, and upload only that.

For the presentations, the presentation would be by one individual.

If the iPhone/Android is your thing, please volunteer.  However, please bear in
mind that many people in class are just starting, so be careful not to talk over
people's heads.

Run:
   I ran this in AndroidStudio and I am not sure how to run it in any other way except to import the project
   
Time:
25ish hours.  Getting AndroidStudio working with a basic  jni triangle program took awhile as I was
originally trying to get Teapots to work.  Then having to figure out most of the basic functions Java gives access to 
but the c++  does not (like matrix operations) took awhile to figure out what I need when I realized I couldn't find
c++ versions.  Almost all of my changes are in gl_code.cpp and GL2JNIView.java.  You can move the object angle by moving your
finger on the screen.  I did this on the Nexus 5x as I couldn't get my Android Emulator working.  Please let me know if
you cannot get it to show on your emulator/android phone(if you  have one) and I will make a video off the app running on my
phone.  I left the original README.md as that may help you to get my project up and running in AndroidStudio.
