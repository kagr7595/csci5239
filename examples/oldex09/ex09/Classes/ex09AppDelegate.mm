#import "ex09AppDelegate.h"

@implementation ex09AppDelegate

//
//  Constructor
//
- (void) applicationDidFinishLaunching: (UIApplication*) application
{
   //  Get sceen size
   CGRect screenBounds = [[UIScreen mainScreen] bounds];
	
   //  Create full screen UI window
   window = [[UIWindow alloc] initWithFrame: screenBounds];
   //  Create full screen GL view
   glview = [[GLView alloc]   initWithFrame: screenBounds];
   //  Map GL view to UI window
   UIViewController *vc = [[UIViewController alloc] init];
   [vc.view addSubview:glview];
   [window setRootViewController:vc];
   //  Give it the focus
   [window makeKeyAndVisible];
}

//
//  Destructor
//
- (void) dealloc
{
   [glview release];
   [window release];
   [super dealloc];
}

@end
