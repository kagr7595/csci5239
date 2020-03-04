//
//  OpenGL widget
//
#include "ex14opengl.h"
#include <math.h>
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

//
//  Constructor
//
Ex14opengl::Ex14opengl(QWidget* parent)
    : CUgl(parent,false)
{
   shape = 0;
   Dim = 8;
}

//
//  Set Objects
//
void Ex14opengl::setShape(int obj)
{
   shape = obj;
}

//
//  Set Objects
//
void Ex14opengl::setSize(int n)
{
   Dim = pow(2,n+3);
}

//
//  Initialize
//
void Ex14opengl::initializeGL()
{
   //  Load shader
   addShader("",":/ex14a.frag");
   addShader("",":/ex14b.frag");
   addShader("",":/ex14c.frag");

   //  Load images
   glGenTextures(1,&img0);
   glBindTexture(GL_TEXTURE_2D,img0);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glGenTextures(1,&img1);
   glBindTexture(GL_TEXTURE_2D,img1);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

   // Load object
   teapot = new Teapot(8);
   teapot->setScale(0.33);
   teapot->setColor(1,1,0);
}

//
//  Draw shape
//
void Ex14opengl::DrawObj(int shape,float dx,float dy,int type)
{
   glPushMatrix();
   glTranslatef(dx,dy,0);
   glColor3f(1,1,0);
   //  Triangle
   if (shape==0)
   {
      glBegin(type);
      glVertex2f(-1,-1);
      glVertex2f(+1,-1);
      glVertex2f(+0,+1);
      glEnd();
   }
   //  Square
   else if (shape==1)
   {
      glBegin(type);
      glVertex2f(-1,-1);
      glVertex2f(+1,-1);
      glVertex2f(+1,+1);
      glVertex2f(-1,+1);
      glEnd();
   }
   //  Diamond
   else if (shape==2)
   {
      glBegin(type);
      glVertex2f( 0,-1);
      glVertex2f(+1, 0);
      glVertex2f( 0,+1);
      glVertex2f(-1, 0);
      glEnd();
   }
   //  Circle
   else if (shape==3)
   {
      glBegin(type);
      int k;
      for (k=0;k<360;k+=10)
         glVertex2f(Cos(k),Sin(k));
      glEnd();
   }
   //  Teapot
   else
      teapot->display();
   glPopMatrix();
}

//
//  Draw all shapes in the scene
//
void Ex14opengl::DrawScene(int type,int dim,int wid,int hgt)
{
   //  Set dimensions so that the shape size in pixels are correct
   double dx = (double)wid/dim;
   double dy = (double)hgt/dim;

   //  Set projection and draw all the shapes
   glPushMatrix();
   glOrtho(-dx,+dx,-dy,+dy,-1,1);
   DrawObj(0,-2,-2,type);
   DrawObj(1,+2,-2,type);
   DrawObj(2,-2,+2,type);
   DrawObj(3,+2,+2,type);
   DrawObj(4, 0, 0,type);
   glPopMatrix();
}

//
//  Draw the window
//
void Ex14opengl::paintGL()
{
   //  Set reference image dimensions
   int dim = Dim;
   int wid = width()*devicePixelRatio();
   int hgt = height()*devicePixelRatio();
   if (wid<dim) dim = wid;
   if (hgt<dim) dim = hgt;

   //  Make test image
   //  Draws the shape
   //  Copy image to texture on unit 0
   glClear(GL_COLOR_BUFFER_BIT);
   doOrtho(wid,hgt);
   DrawScene(GL_POLYGON,dim,wid,hgt);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D,img0);
   glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,0,0,wid,hgt,0);

   //  Make reference image
   //  Limit viewport to dim x dim
   //  Draw shape to fill that size
   //  Copy image to texture on unit 1
   glClear(GL_COLOR_BUFFER_BIT);
   glViewport(0,0,dim,dim);
   DrawObj(shape,0,0,GL_POLYGON);
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D,img1);
   glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,0,0,dim,dim,0);
   glActiveTexture(GL_TEXTURE0);

   //
   //  Process images using the shader
   //
   glClear(GL_COLOR_BUFFER_BIT);
   glViewport(0,0,wid,hgt);
   if (mode==2) DrawScene(GL_LINE_LOOP,dim,wid,hgt);

   shader[mode]->bind();

   //  Set parameters
   float dX = 1.0/wid;
   float dY = 1.0/hgt;
   shader[mode]->setUniformValue("img0",0);
   shader[mode]->setUniformValue("img1",1);
   shader[mode]->setUniformValue("dim",dim);
   shader[mode]->setUniformValue("dX",dX);
   shader[mode]->setUniformValue("dY",dY);

   //  Do the whole screen
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex2f(-1,-1);
   glTexCoord2f(0,1); glVertex2f(-1,+1);
   glTexCoord2f(1,1); glVertex2f(+1,+1);
   glTexCoord2f(1,0); glVertex2f(+1,-1);
   glEnd();

   shader[mode]->release();
}
