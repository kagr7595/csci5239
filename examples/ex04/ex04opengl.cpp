//
//  OpenGL widget
//
#include "ex04opengl.h"
#include "Cube.h"
#include "Icosahedron.h"
#include "WaveOBJ.h"
#include "Teapot.h"

//
//  Constructor
//
Ex04opengl::Ex04opengl(QWidget* parent)
    : CUgl(parent)
{
   t0 = 0;
}

//
//  Initialize
//
void Ex04opengl::initializeGL()
{
   //  Load shaders
   addShader("",":/ex04a.frag");
   addShader(":/ex04b.vert",":/ex04b.frag");
   addShader(":/ex04c.vert",":/ex04c.frag");
   addShader(":/ex04d.vert",":/ex04d.frag");
   addShader(":/ex04e.vert",":/ex04e.frag");

   //  Load objects
   addObject(new Cube(":/crate.png"));
   addObject(new Icosahedron(":/pi.png"));
   addObject(new Teapot(8,":/pi.png",0.5));
   addObject(new WaveOBJ("cruiser.obj",":/"));
   setObject(0);

   //  Set max frame rate
   maxFPS(1);
}

//
//  Draw the window
//
void Ex04opengl::paintGL()
{
   int dt=time.nsecsElapsed();
   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   //  Apply projection
   doModelViewProjection();

   //  Apply lighting
   doLight();

   //  Apply shader
   if (mode) shader[mode]->bind();

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
