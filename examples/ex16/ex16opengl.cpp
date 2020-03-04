//
//  OpenGL widget
//
#include "ex16opengl.h"
#include "Cube.h"
#include "Teapot.h"
#include "WaveOBJ.h"
#include "Noise.h"

//
//  Constructor
//
Ex16opengl::Ex16opengl(QWidget* parent)
    : CUgl(parent)
{
}

//
//  Initialize
//
void Ex16opengl::initializeGL()
{
   //  Load shaders
   addShader(":/ex16.vert",":/ex16a.frag");
   addShader(":/ex16.vert",":/ex16b.frag");
   addShader(":/ex16.vert",":/ex16c.frag");
   addShader(":/ex16.vert",":/ex16d.frag");

   //  Objects
   addObject(new Cube());
   addObject(new Teapot(8));
   addObject(new WaveOBJ("bunny.obj",":/"));
   setObject(0);

   //  Set noise texture
   CreateNoise3D(GL_TEXTURE1);
}

//
//  Draw the window
//
void Ex16opengl::paintGL()
{
   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   //  Apply projection
   doModelViewProjection();

   //  Apply lighting
   doLight();

   //  Apply shader
   if (mode)
   {
      shader[mode]->bind();
      shader[mode]->setUniformValue("Noise3D",1);
   }

   //  Draw scene
   doScene();

   //  Release shader
   if (mode) shader[mode]->release();

   //  Disable lighting
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);
}
