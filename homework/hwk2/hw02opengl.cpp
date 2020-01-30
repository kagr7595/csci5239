//
//  OpenGL widget
//
#include "hw02opengl.h"
#include "Cube.h"
#include "Icosahedron.h"
#include "WaveOBJ.h"
#include "Teapot.h"

//
//  Constructor
//
Hw02opengl::Hw02opengl(QWidget* parent)
    : CUgl(parent)
{
    x0 = 1;
    y0 = 0;
}

//
//  Set X position
//
void Hw02opengl::setX(double X)
{
   x0 = X;
   //  Request redisplay
   update();
}

//
//  Set Y position
//
void Hw02opengl::setY(double Y)
{
   y0 = Y;
   //  Request redisplay
   update();
}


//
//  Initialize
//
void Hw02opengl::initializeGL()
{
   //  Load shaders
   addShader(":/hw02a.vert",":/hw02a.frag");
   addShader(":/hw02b.vert",":/hw02b.frag");

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
void Hw02opengl::paintGL()
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
      QVector3D loc(x0,y0,1);
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
   
}
