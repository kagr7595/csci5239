//
//  OpenGL Ex06opengl Widget
//

#ifndef EX06OPENGL_H
#define EX06OPENGL_H

#include "CUgl.h"
#include <QMatrix4x4>

class Ex06opengl : public CUgl
{
Q_OBJECT
private:
   QOpenGLTexture* tex;          //  Textures
   QOpenGLBuffer   cube_buffer;  //  Vertex buffer
public:
   Ex06opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
protected:
   void initializeGL();  //  Initialize widget
   void paintGL();       //  Draw widget
};

#endif
