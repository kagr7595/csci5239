//
//  OpenGL widget
//
#include "ex03opengl.h"
#include "Cube.h"
#include "Icosahedron.h"
#include "WaveOBJ.h"
#include "Teapot.h"

//
//  Constructor
//
Ex03opengl::Ex03opengl(QWidget* parent)
    : CUgl(parent)
{
   x0 = y0 = 0;
   z0 = 1;
}

//
//  Set X position
//
void Ex03opengl::setX(double X)
{
   x0 = X;
   //  Request redisplay
   update();
}

//
//  Set Y position
//
void Ex03opengl::setY(double Y)
{
   y0 = Y;
   //  Request redisplay
   update();
}

//
//  Set Zoom
//
void Ex03opengl::setZoom(double Z)
{
   z0 = Z;
   //  Request redisplay
   update();
}

//
//  Initialize
//
void Ex03opengl::initializeGL()
{
   //  Load shaders
   addShader(":/ex03a.vert",":/ex03a.frag");
   addShader(":/ex03a.vert",":/ex03b.frag");
   addShader(":/ex03b.vert",":/ex03c.frag");
   addShader(":/ex03b.vert",":/ex03d.frag");
   addShader(":/ex03b.vert",":/ex03e.frag");

   // Load objects
   addObject(new Cube(":/pi.png"));
   addObject(new Icosahedron(":/pi.png"));
   addObject(new Teapot(8,":/pi.png",0.5,Color(0,1,1)));
   addObject(new WaveOBJ("suzanne.obj",":/",1.0));
   setObject(0);
}

//
//  Draw the window
//
void Ex03opengl::paintGL()
{
   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   //  Apply projection
   doModelViewProjection();

   //  Enable lighting
   doLight();

   //  Apply shader
   if (mode)
   {
      shader[mode]->bind();
      //  Dimensions
      QVector3D loc(x0,y0,1/z0);
      shader[mode]->setUniformValue("loc",loc);
      //  Time
      float t = getTime();
      shader[mode]->setUniformValue("time",t);
   }

   //  Draw scene
   doScene();

   //  Release shader
   if (mode) shader[mode]->release();
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);
   
   //  Emit centers to display
   emit zoom(QString::number((int)z0));
}
