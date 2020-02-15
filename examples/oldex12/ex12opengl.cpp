//
//  OpenGL widget
//
#include "ex12opengl.h"

//
//  Constructor
//
Ex12opengl::Ex12opengl(QWidget* parent)
    : CUgl(parent)
{
   N = 1;
   x0 = y0 = 0;
   zoom = 1;
   Cw = Ch = 0;
   frame = NULL;
   framebuf[0] = NULL;
   framebuf[1] = NULL;
}

//
//  Reset view
//
void Ex12opengl::reset()
{
   x0 = y0 = 0;
   zoom = 1;
   //  Request redisplay
   update();
}

//
//  Set passes
//
void Ex12opengl::setPasses(int n)
{
   N = n;
   //  Request redisplay
   update();
}

//
//  Set image
//
void Ex12opengl::setImage(QImage img)
{
   //  Capture context
   makeCurrent();
   //  Copy image to texture
   if (frame) delete frame;
   frame = new QOpenGLTexture(img.mirrored());
   //  Image size
   Cw = img.width();
   Ch = img.height();
   //  Allocate frame buffer objects to native camera resolution
   if (!framebuf[0] || framebuf[0]->width() != Cw|| framebuf[0]->height() != Ch)
   {
      for (int k=0;k<2;k++)
      {
         //  Allocate frame buffer objects
         if (framebuf[k]) delete framebuf[k];
         framebuf[k] = new QOpenGLFramebufferObject(Cw,Ch);
      }
   }
   //  Request redisplay
   update();
}

//
//  Initialize
//
void Ex12opengl::initializeGL()
{
   //  Load shaders
   addShader("",":/ex12a.frag");
   addShader("",":/ex12b.frag");
   addShader("",":/ex12c.frag");
   addShader("",":/ex12d.frag");
   addShader("",":/ex12e.frag");
   addShader("",":/ex12f.frag");
   addShader("",":/ex12g.frag");
   addShader("",":/ex12h.frag");
}

//
//  Draw the window
//
void Ex12opengl::paintGL()
{
   if (!frame) return;
   //  Starting texture
   glEnable(GL_TEXTURE_2D);
   frame->bind();
   //  Camera aspect ratio
   float Casp = Cw / (float)Ch;

   //  Process
   if (mode)
   {
      //  Set Projection
      doOrtho(Cw,Ch);

      //  Enable shader
      shader[mode]->bind();

      //  Set shader increments
      shader[mode]->setUniformValue("dX",(float)1.0/Cw);
      shader[mode]->setUniformValue("dY",(float)1.0/Ch);

      //  Ping-Pong at camera resolution
      for (int k=0;k<N;k++)
      {
         //  Pick nearest pixel
         glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
         //  Set output buffer
         framebuf[k%2]->bind();
         //  Draw image
         glClear(GL_COLOR_BUFFER_BIT);
         glBegin(GL_QUADS);
         glTexCoord2f(0,0); glVertex2f(-Casp,-1);
         glTexCoord2f(1,0); glVertex2f(+Casp,-1);
         glTexCoord2f(1,1); glVertex2f(+Casp,+1);
         glTexCoord2f(0,1); glVertex2f(-Casp,+1);
         glEnd();
         //  Release output buffer
         framebuf[k%2]->release();
         //  Bind texture to result
         glBindTexture(GL_TEXTURE_2D,framebuf[k%2]->texture());
      }

      //  Release shader
      shader[mode]->release();
   }

   //  Set pixel interpolation
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   //  Projection with zoom and pan
   int w = width()*devicePixelRatio();
   int h = height()*devicePixelRatio();
   doOrtho(w,h,zoom,x0,y0);
   //  Draw to screen
   glClear(GL_COLOR_BUFFER_BIT);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex2f(-Casp,-1);
   glTexCoord2f(1,0); glVertex2f(+Casp,-1);
   glTexCoord2f(1,1); glVertex2f(+Casp,+1);
   glTexCoord2f(0,1); glVertex2f(-Casp,+1);
   glEnd();
   //  Done with textures
   glDisable(GL_TEXTURE_2D);
}

/******************************************************************/
/*************************  Mouse Events  *************************/
/******************************************************************/
//
//  Mouse moved
//
void Ex12opengl::mouseMoveEvent(QMouseEvent* e)
{
   if (mouse)
   {
      QPoint d = e->pos()-pos;      //  Change in mouse location
      x0 += d.x()/(zoom*width());   //  Translate x movement to azimuth
      y0 -= d.y()/(zoom*height());  //  Translate y movement to elevation
      pos = e->pos();               //  Remember new location
      update();                     //  Request redisplay
   }
}

//
//  Mouse wheel
//
void Ex12opengl::wheelEvent(QWheelEvent* e)
{
   //  Zoom out
   if (e->delta()<0)
      zoom *= 1.05;
   //  Zoom in
   else if (zoom>1)
      zoom /= 1.05;
   //  Request redisplay
   update();
}
