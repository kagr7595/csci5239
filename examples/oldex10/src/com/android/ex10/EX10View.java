/*
 *  Example 10:  Surface view
 */

package com.android.ex10;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.os.SystemClock;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

/*
 * A simple GLSurfaceView sub-class that demonstrate how to perform
 * OpenGL ES 2.0 rendering into a GL Surface. Note the following important
 * details:
 *
 * - The class must use a custom context factory to enable 2.0 rendering.
 *   See ContextFactory class definition below.
 *
 * - The class must use a custom EGLConfigChooser to be able to select
 *   an EGLConfig that supports 2.0. This is done by providing a config
 *   specification to eglChooseConfig() that has the attribute
 *   EGL10.ELG_RENDERABLE_TYPE containing the EGL_OPENGL_ES2_BIT flag
 *   set. See ConfigChooser class definition below.
 *
 * - The class must select the surface's format, then choose an EGLConfig
 *   that matches it exactly (with regards to red/green/blue/alpha channels
 *   bit depths). Failure to do so would result in an EGL_BAD_MATCH error.
 */
class EX10View extends GLSurfaceView
{
   private static String TAG = "EX10View";

   //  Constructor
   public EX10View(Context context)
   {
      super(context);
      init(false,false, 8, 0);
   }

   //  Initialize
   private void init(boolean ES2,boolean translucent,int depth,int stencil)
   {
      // By default, GLSurfaceView() creates a RGB_565 opaque surface.
      // If we want a translucent one, we should change the surface's
      // format here, using PixelFormat.TRANSLUCENT for GL Surfaces
      // is interpreted as any 32-bit surface with alpha by SurfaceFlinger.
      if (translucent) this.getHolder().setFormat(PixelFormat.TRANSLUCENT);

      // Setup the context factory for 2.0 rendering.
      // See ContextFactory class definition below
//    setEGLContextFactory(new ContextFactory());

      // We need to choose an EGLConfig that matches the format of
      // our surface exactly. This is going to be done in our
      // custom config chooser. See ConfigChooser class definition
      // below.
      setEGLConfigChooser(translucent ?
                          new ConfigChooser(ES2 , 8,8,8, 8, depth, stencil) :
                          new ConfigChooser(ES2 , 5,6,5, 0, depth, stencil) );

      // Set the renderer responsible for frame rendering
      setRenderer(new Renderer());
   }

   //
   //  Subclass to get window properties
   //
   private static class ContextFactory implements GLSurfaceView.EGLContextFactory
   {
      private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
      public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig)
      {
         Log.w(TAG, "creating OpenGL ES 1.0 context");
         checkEglError("Before eglCreateContext", egl);
         int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION,1,EGL10.EGL_NONE };
         EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
         checkEglError("After eglCreateContext", egl);
         return context;
      }

      public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context)
      {
         egl.eglDestroyContext(display, context);
      }
   }

   private static void checkEglError(String prompt, EGL10 egl)
   {
      int error;
      while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS)
      {
         Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
      }
   }

   //
   //  Subclass to select the window properties
   //
   private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser
   {
      protected int mRedSize;
      protected int mGreenSize;
      protected int mBlueSize;
      protected int mAlphaSize;
      protected int mDepthSize;
      protected int mStencilSize;
      private int[] mValue = new int[1];

      public ConfigChooser(boolean ES2,int r, int g, int b, int a, int depth, int stencil)
      {
         mRedSize = r;
         mGreenSize = g;
         mBlueSize = b;
         mAlphaSize = a;
         mDepthSize = depth;
         mStencilSize = stencil;
      }

      // This EGL config specification is used to specify 2.0 rendering.
      // We use a minimum size of 4 bits for red/green/blue, but will
      // perform actual matching in chooseConfig() below.
      private static int EGL_OPENGL_ES2_BIT = 4;
      private static int[] s_configAttribs2 =
      {
         EGL10.EGL_RED_SIZE, 0,//4,
         EGL10.EGL_GREEN_SIZE, 0, //4,
         EGL10.EGL_BLUE_SIZE, 0, //4,
         //EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
         EGL10.EGL_NONE
      };

      public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display)
      {
         // Get the number of minimally matching EGL configurations
         int[] num_config = new int[1];
            
         boolean bRet = egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);
         if (bRet == false)
         {
            Log.v("EX10View", "eglChooseConfig failed"); 
            int nRet = egl.eglGetError();
            if (nRet == egl.EGL_BAD_DISPLAY)
               Log.v("EX10View", "Bad EGL display."); 
            else if (nRet == egl.EGL_BAD_ATTRIBUTE)
               Log.v("EX10View", "Bad attribute."); 
            else if (nRet == egl.EGL_NOT_INITIALIZED)
               Log.v("EX10View", "GL not initialized"); 
            else if (nRet == egl.EGL_BAD_PARAMETER)
               Log.v("EX10View", "Bad parameter."); 
            else
               Log.v("EX10View", "Other error."); 
         }
         else
            Log.v("EX10View", "eglChooseConfig succeeded");

         int numConfigs = num_config[0];               
         if (numConfigs <= 0) throw new IllegalArgumentException("No configs match configSpec");

         // Allocate then read the array of minimally matching EGL configs
         EGLConfig[] configs = new EGLConfig[numConfigs];
         egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);

         // Now return the "best" one
         return chooseConfig(egl, display, configs);
      }

      public EGLConfig chooseConfig(EGL10 egl,EGLDisplay display,EGLConfig[] configs)
      {
         for(EGLConfig config : configs)
         {
            int d = findConfigAttrib(egl, display, config, EGL10.EGL_DEPTH_SIZE, 0);
            int s = findConfigAttrib(egl, display, config, EGL10.EGL_STENCIL_SIZE, 0);

            // We need at least mDepthSize and mStencilSize bits
            if (d < mDepthSize || s < mStencilSize) continue;

            // We want an *exact* match for red/green/blue/alpha
            int r = findConfigAttrib(egl, display, config, EGL10.EGL_RED_SIZE,   0);
            int g = findConfigAttrib(egl, display, config, EGL10.EGL_GREEN_SIZE, 0);
            int b = findConfigAttrib(egl, display, config, EGL10.EGL_BLUE_SIZE,  0);
            int a = findConfigAttrib(egl, display, config, EGL10.EGL_ALPHA_SIZE, 0);

            if (r == mRedSize && g == mGreenSize && b == mBlueSize && a == mAlphaSize) return config;
         }
         return null;
      }

      private int findConfigAttrib(EGL10 egl, EGLDisplay display, EGLConfig config, int attribute, int defaultValue)
      {
         if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) { return mValue[0]; }
           return defaultValue;
      }
   }

   private static class Renderer implements GLSurfaceView.Renderer
   {
      public void onDrawFrame(GL10 gl)
      {
         float t = 0.001f*SystemClock.uptimeMillis();
         EX10Lib.step(t);
      }

      public void onSurfaceChanged(GL10 gl,int width,int height)
      {
         EX10Lib.init(width,height);
      }

      public void onSurfaceCreated(GL10 gl,EGLConfig config)
      {
         // Do nothing.
      }
   }
}
