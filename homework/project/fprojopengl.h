//
//  OpenGL Fprojopengl Widget
//

#ifndef FProjOPENGL_H
#define FProjOPENGL_H

#include "CUgl.h"
#include <QMatrix4x4>

class Fprojopengl : public CUgl
{
Q_OBJECT
private:
   QOpenGLTexture* tex;          //  Textures
   QOpenGLBuffer   cube_buffer;  //  Vertex buffer
public:
   Fprojopengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
protected:
   void initializeGL();  //  Initialize widget
   void paintGL();       //  Draw widget
};

#endif
