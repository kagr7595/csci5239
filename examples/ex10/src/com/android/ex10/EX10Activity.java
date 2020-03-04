/*
 *  Example 10:  Activities
 */

package com.android.ex10;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.content.res.Configuration;

public class EX10Activity extends Activity
{
   EX10View view;

   @Override protected void onCreate(Bundle icicle)
   {
      super.onCreate(icicle);
      Log.d("Example10","On create"); 	
      view = new EX10View(getApplication());
      setContentView(view);
   }

   @Override protected void onPause()
   {
      super.onPause();
      Log.d("Example10","On resume"); 
      view.onPause();
   }

   @Override protected void onResume()
   {
      super.onResume();
      Log.d("Example10","On resume"); 
      view.onResume();
   }

   @Override public void onConfigurationChanged(Configuration conf)
   {
      super.onConfigurationChanged(conf);
      //  int angle = (conf.orientation == Configuration.ORIENTATION_LANDSCAPE) ? 90 : 0;
      //  This is utterly insane, but hardKeyboadHidden detects landscape/portrait in the emulator
      int angle = (conf.hardKeyboardHidden == 2) ? 90 : 0;
      Log.d("Example10","On ConfigurationChanged "+angle); 
      EX10Lib.rotate(angle);
   }
}
