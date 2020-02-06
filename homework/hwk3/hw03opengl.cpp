//
//  OpenGL widget
//
#include "hw03opengl.h"
#include "Cube.h"
#include "Icosahedron.h"
#include "WaveOBJ.h"
#include "Teapot.h"

//
//  Constructor
//
Hw03opengl::Hw03opengl(QWidget* parent)
    : CUgl(parent)
{
    x0 = 1;
    y0 = 0;
    t0 = 0;
}

//
//  Set X position
//
void Hw03opengl::setX(double X)
{
   x0 = X;
   //  Request redisplay
   update();
}

//
//  Set Y position
//
void Hw03opengl::setY(double Y)
{
   y0 = Y;
   //  Request redisplay
   update();
}


//
//  Initialize
//
void Hw03opengl::initializeGL()
{
   //  Load shaders
   addShader(":/hw03a.vert",":/hw03a.frag");
   addShader(":/hw03a.vert",":/hw03a_1.frag");
   addShader(":/hw03a.vert",":/hw03a_2.frag");
   addShader(":/hw03a_1.vert",":/hw03a.frag");
   addShader(":/hw03a_2.vert",":/hw03a.frag");
   addShader(":/hw03b.vert",":/hw03b.frag");
   addShader(":/hw03b.vert",":/hw03b_1.frag");
   addShader(":/hw03b.vert",":/hw03b_2.frag");
   addShader(":/hw03b_1.vert",":/hw03b.frag");
   addShader(":/hw03b_2.vert",":/hw03b.frag");

   // Load objects
   addObject(new Cube(":/pi.png"));
   addObject(new Icosahedron(":/pi.png"));
   addObject(new Teapot(8,":/pi.png",0.5,Color(0,1,1)));
   addObject(new WaveOBJ("suzanne.obj",":/",1.0));
   setObject(0);

   //  Set max frame rate
   maxFPS(1);
}

//
//  Draw the window
//
void Hw03opengl::paintGL()
{
   int dt=time.nsecsElapsed();
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

   //  Frame estimator
   dt = time.nsecsElapsed()-dt;
   if (t0!=time.elapsed()/1000)
   {
      emit fps(QString::number(int(1e9/dt)));
      t0 = time.elapsed()/1000;
   }
   
}
