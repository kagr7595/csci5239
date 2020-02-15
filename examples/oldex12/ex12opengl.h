//
//  OpenGL Ex12opengl Widget
//

#ifndef EX12OPENGL_H
#define EX12OPENGL_H

#include "CUgl.h"
#include <QImage>

class Ex12opengl : public CUgl
{
Q_OBJECT
private:
   int     N;                             //  Number of passes
   float   x0,y0;                         //  Image center
   float   zoom;                          //  Zoom
   int     Cw,Ch;                         //  Camera image size
   QOpenGLTexture*           frame;       //  Image frame
   QOpenGLFramebufferObject* framebuf[2]; //  Framebuffers
public:
   Ex12opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
   void setPasses(int pass);              //  Slot to set number of passes
   void setImage(QImage img);             //  Slot to set image
   void reset();                          //  Reset view
protected:
   void initializeGL();                   //  Initialize widget
   void paintGL();                        //  Draw widget
   void mouseMoveEvent(QMouseEvent*);     // Mouse moved
   void wheelEvent(QWheelEvent*);         // Mouse wheel
};

#endif
