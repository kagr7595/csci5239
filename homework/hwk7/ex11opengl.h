//
//  OpenGL Ex11opengl Widget
//

#ifndef EX11OPENGL_H
#define EX11OPENGL_H

#include "CUgl.h"

class Ex11opengl : public CUgl
{
Q_OBJECT
private:
   int     N;         //  Nomber of passes
   float   x0,y0;     //  Object center
   float   z0;        //  Zoom
   QOpenGLFramebufferObject* framebuf[2]; //  Framebuffers
public:
   Ex11opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
    void setPasses(int pass);  //  Slot to set number of passes
protected:
    void initializeGL();       //  Initialize widget
    void resizeGL(int,int);    //  Resize widget
    void paintGL();            //  Draw widget
};

#endif
