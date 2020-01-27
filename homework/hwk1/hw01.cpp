//
//  Hw01:  NDC to RGB shader (It says RGB to NDC but the lecture video and slides say to do NDC to RGB)
//  Kathy Grimes
//  CSCI 5239 Spring 2020
//  Based off of CSCI5239 Class Ex01
//

#include <QApplication>
#include "hw01viewer.h"

//
//  Main function
//
int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);
   //  Create and show view widget
   Hw01viewer view;
   view.show();
   //  Main loop for application
   return app.exec();
}
