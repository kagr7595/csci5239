//
//  Hw04:  OpenGL 4
//  Willem A. (Vlakkies) Schreuder
//  CSCI 4239/5239 Spring 2019
//

#include <QApplication>
#include "hw04viewer.h"

//
//  Main function
//
int main(int argc, char *argv[])
{
   //  Create the application
   QApplication app(argc,argv);
   //  Create and show view widget
   Hw04viewer view;
   view.show();
   //  Main loop for application
   return app.exec();
}
