/*
 *  Example 10:  Wrapper to native library
 */

package com.android.ex10;

public class EX10Lib
{
   static
   {
      System.loadLibrary("ex10");
   }

   public static native void init(int width,int height);
   public static native void step(float t);
   public static native void rotate(int angle);
}
