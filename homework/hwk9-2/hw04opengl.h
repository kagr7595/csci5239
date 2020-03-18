//
//  OpenGL Hw04opengl Widget
//

#ifndef HW04OPENGL_H
#define HW04OPENGL_H

#include "CUgl.h"
#include <QMatrix4x4>

class Hw04opengl : public CUgl
{
Q_OBJECT
private:
   QOpenGLTexture* tex;          //  Textures
   QOpenGLBuffer   cube_buffer;  //  Vertex buffer
public:
   Hw04opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
protected:
   void initializeGL();  //  Initialize widget
   void paintGL();       //  Draw widget
};

#endif
