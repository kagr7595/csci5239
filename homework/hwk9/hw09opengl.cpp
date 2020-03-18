//
//  OpenGL widget
//
#include "hw09opengl.h"
#include "Cube.h"
#include "WaveOBJ.h"
#include "Teapot.h"

//
//  Constructor
//
Hw09opengl::Hw09opengl(QWidget* parent)
    : CUgl(parent)
{
   N = 1;
   framebuf[0] = NULL;
   framebuf[1] = NULL;
}

//
//  Set passes
//
void Hw09opengl::setPasses(int n)
{
   N = n;
   //  Request redisplay
   update();
}

//
//  Initialize
//
void Hw09opengl::initializeGL()
{
   //  Load shaders
   addShader("",":/hw09a.frag");
   addShader("",":/hw09b.frag");
   addShader("",":/hw09c.frag");
   addShader("",":/hw09d.frag");
   addShader("",":/hw09e.frag");
   addShader("",":/hw09f.frag");
   addShader("",":/hw09g.frag");
   addShader("",":/hw09h.frag");

   // Cube
   Cube* cube = new Cube();
   cube->setScale(0.5,0.5,0.5);
   cube->setTranslate(1,1,0);
   addObject(cube);

   // Teapot
   Teapot* pot = new Teapot(8);
   pot->setScale(0.3);
   pot->setTexture(":/water.png");
   pot->setTranslate(-1,1,0);
   addObject(pot);

   // Cruiser
   WaveOBJ* cruiser=0;
   try
   {
      cruiser = new WaveOBJ("cruiser.obj",":/");
   }
   catch (QString err)
   {
      Fatal("Error loading object\n"+err);
   }
   if (cruiser)
   {
      cruiser->setColor(1,1,0);
      cruiser->setScale(1.0);
      cruiser->setTranslate(0,-1,0);
      addObject(cruiser);
   }
}

//
//  Create new framebuffers when window is resized
//
void Hw09opengl::resizeGL(int width, int height)
{
   //  Manage retina displays
   int w = width*devicePixelRatio();
   int h = height*devicePixelRatio();
   //  Framebuffer 0 needs a Z-buffer
   if (framebuf[0]) delete framebuf[0];
   framebuf[0] = new QOpenGLFramebufferObject(w,h,QOpenGLFramebufferObject::Depth);
   //  Framebuffer 1 does not need a Z-buffer
   if (framebuf[1]) delete framebuf[1];
   framebuf[1] = new QOpenGLFramebufferObject(w,h);
}

//
//  Draw the window
//
void Hw09opengl::paintGL()
{
   //  Send output to framebuf[0]
   if (mode) framebuf[0]->bind();

   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   //  Apply projection
   doModelViewProjection();

   //  Apply lighting
   doLight();

   //  Draw scene
   doScene();

   //  Disable lighting and depth
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);

   //  Apply shader
   if (mode)
   {
      //  Reset projections
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();

      //  Enable shader
      shader[mode]->bind();

      //  Set shader increments
      float dX = 1.0/width();
      float dY = 1.0/height();
      shader[mode]->setUniformValue("dX",dX);
      shader[mode]->setUniformValue("dY",dY);

      //  Ping-Pong
      for (int k=0;k<N;k++)
      {
         int last = k%2;
         int next = 1-last;
         //  Set output to next framebuffer except for the last pass
         if (k+1<N)
            framebuf[next]->bind();
         else
            framebuf[last]->release();
         //  Get the texture
         glBindTexture(GL_TEXTURE_2D,framebuf[last]->texture());
         //  Exercise shader
         glClear(GL_COLOR_BUFFER_BIT);
         glBegin(GL_QUADS);
         glTexCoord2f(0,0); glVertex2f(-1,-1);
         glTexCoord2f(1,0); glVertex2f(+1,-1);
         glTexCoord2f(1,1); glVertex2f(+1,+1);
         glTexCoord2f(0,1); glVertex2f(-1,+1);
         glEnd();
      }

      //  Release shader
      shader[mode]->release();

      //  Undo transformations
      glPopMatrix();
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
   }
}
