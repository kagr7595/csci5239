//
//  OpenGL Ex13opengl Widget
//

#ifndef EX13OPENGL_H
#define EX13OPENGL_H

#include "CUgl.h"

class Ex13opengl : public CUgl
{
Q_OBJECT
private:
   float   x0,y0;           //  Image center
   float   zoom;            //  Zoom
   int     w,h;             //  Image size
   int     frac;            //  Image fraction
   QOpenGLTexture* tex[2];  //  Images
public:
   Ex13opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
   void setFrac(int pct);                 //  Slot to set fraction
   void setMode(int mode);                //  Slot to set mode
   void reset();                          //  Reset view
protected:
   void initializeGL();                   //  Initialize widget
   void paintGL();                        //  Draw widget
   void mouseMoveEvent(QMouseEvent*);     //  Mouse moved
   void wheelEvent(QWheelEvent*);         //  Mouse wheel
};

#endif
