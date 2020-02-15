Example 10:  Android OpenGL ES

This program borrows heavily from the HellowArrow example in iPhone 3D
Programming by Philip Rideout.  The basic framework is the same, but
the program has ben modified to draw a 3D cube instead of a 2D arrow.

INSTALLING THE SDK AND NDK

On Ubuntu install ant and 32-bit packages if needed
  sudo apt-get install ant lib32z1 lib32stdc++6
Download the android SDK and unpack it
  wget -nd -nH -m http://dl.google.com/android/android-sdk_r24.0.2-linux.tgz
  tar xzvf android-sdk_r24.0.2-linux.tgz
Update the packages
  cd android-sdk-linux
  tools/android update sdk
  Accept the defaults by clicking "Install packages"
  Create a device by clicking "Tools>Manage AVDs" and create a device.
  Start the device (this is really SLOOOOOOW).
Download and install the NDK
  wget -nd -nH -m http://dl.google.com/android/ndk/android-ndk-r10d-linux-x86_64.bin
  chmod a+x android-ndk-r10d-linux-x86_64.bin  
  ./android-ndk-r10d-linux-x86_64.bin
Set your PATH to pick up
   ..../android-sdk-linux_x86/tools
   ..../android-sdk-linux_x86/platform-tools
   ..../android-ndk-r10d

BUILDING

This code has been tested only on the Android emulator and is hard wired to
ONLY use OpenGL ES 1.1.

You can build the project using as 'make'.
To install to the device, start up the emulator and do 'make install'.

This build is set for Rev 21
You need to change this to the rev you are using.
This is especially true if you are building for an actual device.

RUNNING:

In the emulator, click on 'ex10'.
Press the '7' and '9' keys on the keypad to orient the device.
