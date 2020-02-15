#  Build the apk - this is what you upload to the device
bin/EX10Activity-debug.apk:build.xml libs/armeabi/libex10.so src/com/android/ex10/EX10Activity.java src/com/android/ex10/EX10Lib.java src/com/android/ex10/EX10View.java
	ant debug

#  Build the JNI library
libs/armeabi/libex10.so:jni/Android.mk jni/cube.h jni/glview.cpp jni/RenderingEngine.h jni/RenderingEngine.cpp jni/RenderingEngine1.cpp jni/RenderingEngine2.cpp
	ndk-build -B

#  Build the XML from the manifest
build.xml:AndroidManifest.xml
	android update project -p .

#  Install to emulator (or device)
install:bin/EX10Activity-debug.apk
	adb install -r bin/EX10Activity-debug.apk

#  Clean out
clean:
	rm -Rf proguard* local.properties build.xml bin obj libs gen
