//
//  OpenGL widget
//
#include "ex13opengl.h"

//
//  Constructor
//
Ex13opengl::Ex13opengl(QWidget* parent)
    : CUgl(parent,false)
{
   x0 = y0 = 0;
   zoom = 1;
   frac = 0;
}

//
//  Reset view
//
void Ex13opengl::reset()
{
   x0 = y0 = 0;
   zoom = 1;
   frac = 0;
   //  Request redisplay
   update();
}

//
//  Set mode
//
void Ex13opengl::setMode(int m)
{
   mode = m;
   //  Request redisplay
   update();
}

//
//  Set shader
//
void Ex13opengl::setFrac(int pct)
{
   frac = pct;
   //  Request redisplay
   update();
}

//
//  Initialize
//
void Ex13opengl::initializeGL()
{
   //  Load shader
   addShader("",":/ex13.frag");

   //  Load textures
   tex[0] = loadImage(":/20090602.png");
   tex[1] = loadImage(":/20090706.png");
}

//
//  Draw the window
//
void Ex13opengl::paintGL()
{
   //  Map first image to texture unit 0
   glActiveTexture(GL_TEXTURE0);
   tex[0]->bind();
   //  Map second image to texture unit 1
   glActiveTexture(GL_TEXTURE1);
   tex[1]->bind();

   //  Enable shader
   shader[0]->bind();

   //  Set pixel increments
   shader[0]->setUniformValue("img0",0);
   shader[0]->setUniformValue("img1",1);
   shader[0]->setUniformValue("frac",(float)(frac/100.0));
   shader[0]->setUniformValue("mode",mode);

   //  Projection with zoom and pan
   int w = width()*devicePixelRatio();
   int h = height()*devicePixelRatio();
   doOrtho(w,h,zoom,x0,y0);

   //  Draw to screen
   glClear(GL_COLOR_BUFFER_BIT);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex2f(-1,-1);
   glTexCoord2f(1,0); glVertex2f(+1,-1);
   glTexCoord2f(1,1); glVertex2f(+1,+1);
   glTexCoord2f(0,1); glVertex2f(-1,+1);
   glEnd();

   //  Done with shader
   shader[0]->release();
}

/******************************************************************/
/*************************  Mouse Events  *************************/
/******************************************************************/
//
//  Mouse moved
//
void Ex13opengl::mouseMoveEvent(QMouseEvent* e)
{
   if (mouse)
   {
      QPoint d = e->pos()-pos;      //  Change in mouse location
      x0 += d.x()/(zoom*width());   //  Translate x movement to azimuth
      y0 -= d.y()/(zoom*height());  //  Translate y movement to elevation
      pos = e->pos();               //  Remember new location
      update();                   //  Request redisplay
   }
}

//
//  Mouse wheel
//
void Ex13opengl::wheelEvent(QWheelEvent* e)
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
