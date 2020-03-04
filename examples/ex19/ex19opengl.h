//
//  OpenGL Ex19opengl Widget
//

#ifndef EX19OPENGL_H
#define EX19OPENGL_H

#include "CUgl.h"

class Ex19opengl : public CUgl
{
Q_OBJECT
private:
   int     N;         //  Particle count
   float   zh;        //  Light position
   int     n;         //  Particle count
   float*  Vert;      //  Vertices
   float*  Color;     //  Colors
   float*  Vel;       //  Velocities
   float*  Start;     //  Start time
   QOpenGLTexture* tex; //  Texture
public:
   Ex19opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
   void setMode(int m);  //  Setmode
protected:
   void initializeGL();  //  Initialize widget
   void paintGL();       //  Draw widget
private:
  void InitPart();
  void DrawPart();
};

#endif
