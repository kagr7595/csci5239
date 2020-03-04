//
//  Ex18:  Gameof Life
//  Willem A. (Vlakkies) Schreuder
//  CSCI 4239/5239 Spring 2019
//

#include <QApplication>
#include <QSurfaceFormat>
#include "ex18main.h"

int main(int argc,char *argv[])
{
   QApplication app(argc,argv);

   //  Disable VSYNC
   QSurfaceFormat format;
   format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
   format.setSwapInterval(0);
   QSurfaceFormat::setDefaultFormat(format);

   //  RLE file may be specified on the command line
   QString file;
   if (argc>1) file = argv[1];

   //  Start
   Ex18main mainwin(file);
   mainwin.show();
   return app.exec();
}
