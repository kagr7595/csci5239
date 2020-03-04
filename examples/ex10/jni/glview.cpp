// JNI interface

#include <jni.h>
#include "RenderingEngine.h"

extern "C"
{
   JNIEXPORT void JNICALL Java_com_android_ex10_EX10Lib_init(JNIEnv* env,jobject obj,jint width,jint height);
   JNIEXPORT void JNICALL Java_com_android_ex10_EX10Lib_step(JNIEnv* env,jobject obj,jfloat t);
   JNIEXPORT void JNICALL Java_com_android_ex10_EX10Lib_rotate(JNIEnv* env,jobject obj,jint angle);
};

static RenderingEngine* renderer;
JNIEXPORT void JNICALL Java_com_android_ex10_EX10Lib_init(JNIEnv* env,jobject obj,jint width,jint height)
{
   renderer = CreateRenderer1();
   renderer->Initialize(width,height);
}

JNIEXPORT void JNICALL Java_com_android_ex10_EX10Lib_step(JNIEnv* env,jobject obj,jfloat t)
{
   renderer->UpdateAnimation(t);
   renderer->Display(t);
}

JNIEXPORT void JNICALL Java_com_android_ex10_EX10Lib_rotate(JNIEnv* env,jobject obj,jint angle)
{
   renderer->OnRotate(angle);
}
