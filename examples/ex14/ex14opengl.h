//
//  OpenGL Ex14opengl Widget
//

#ifndef EX14OPENGL_H
#define EX14OPENGL_H

#include "CUgl.h"
#include "Teapot.h"

class Ex14opengl : public CUgl
{
Q_OBJECT
private:
   int shape;        // Shape
   int Dim;          // Image Size
   Teapot* teapot;   //  Teapot object
   unsigned int img0,img1;  // Textures
public:
   Ex14opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
   void setShape(int);    //  Shape to find
   void setSize(int);     //  Set size
protected:
   void initializeGL();   //  Initialize widget
   void paintGL();        //  Draw widget
private:
   void DrawObj(int shape,float dx,float dy,int type);  // Draw single object
   void DrawScene(int type,int dim,int wid,int hgt);    // Draw scene
};

#endif
