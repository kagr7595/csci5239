//
//  Ex20: nBody Simulator
//  Willem A. (Vlakkies) Schreuder
//  CSCI 4239/5239 Spring 2019
//

#include <QApplication>
#include "ex20viewer.h"

//
//  Main function
//
int main(int argc, char *argv[])
{
   //  Disable VSYNC
   QSurfaceFormat format;
   format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
   format.setSwapInterval(0);
   QSurfaceFormat::setDefaultFormat(format);

   //  Create the application
   QApplication app(argc,argv);
   //  Create and show view widget
   Ex20viewer view;
   view.show();
   //  Main loop for application
   return app.exec();
}
