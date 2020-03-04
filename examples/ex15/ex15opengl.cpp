//
//  OpenGL widget
//
#include "ex15opengl.h"
#include "Sphere.h"
#include <math.h>
#define Cos(th) cos(M_PI/180*(th))

//
//  Constructor
//
Ex15opengl::Ex15opengl(QWidget* parent)
    : CUgl(parent,false)
{
   mode = 0;
   pct  = 0;
}

//
//  Set mode
//
void Ex15opengl::setMode(int m)
{
   mode = m;
   //  Request redisplay
   update();
}

//
//  Set position
//
void Ex15opengl::setPos(int p)
{
   pct = 0.01*p;
   //  Request redisplay
   update();
}

//
//  Initialize
//
void Ex15opengl::initializeGL()
{
   //  Set projection
   setDim(1.5);
   setPerspective(1);

   //  Load shaders
   addShader(":/ex15.vert",":/ex15.frag");

   //  Draw sphere
   addObject(new Sphere(8));

   //  Load textures
   day[0]  = loadImage(":/day01.jpg");
   day[1]  = loadImage(":/day02.jpg");
   day[2]  = loadImage(":/day03.jpg");
   day[3]  = loadImage(":/day04.jpg");
   day[4]  = loadImage(":/day05.jpg");
   day[5]  = loadImage(":/day06.jpg");
   day[6]  = loadImage(":/day07.jpg");
   day[7]  = loadImage(":/day08.jpg");
   day[8]  = loadImage(":/day09.jpg");
   day[9]  = loadImage(":/day10.jpg");
   day[10] = loadImage(":/day11.jpg");
   day[11] = loadImage(":/day12.jpg");
   night   = loadImage(":/night.jpg");
   cge     = loadImage(":/cge.png");
}

//
//  Draw the window
//
void Ex15opengl::paintGL()
{
   //  Wall time (15 second increments)
   float t = 0.001*time.elapsed()/15;
   float f = t-int(t);
   float zh = mode ? 360*f : 360*pct;

   //  Time of year
   float foy = mode ? pct : f;

   //  Compute month and day
   int dy = 365*fmod(foy,1)+1;
   int ndm[] = {31,28,31,30,31,30,31,31,30,31,30,31};
   int mo = 0;
   while (dy>ndm[mo])
      dy -= ndm[mo++];
   float frac = (dy-1)/(float)ndm[mo];
   mo++;
   char date[8];
   sprintf(date,"%.2d/%.2d",mo,dy);
   emit datim(QString(date));

   //  Z-buffer
   glEnable(GL_DEPTH_TEST);
   //  Clear screen and depth buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //  Apply projection
   doModelViewProjection();

   //  Set light
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_NORMALIZE);
   float Ambient[]  = {0.1,0.1,0.1,1.0};
   float Diffuse[]  = {0.3,0.3,0.3,1.0};
   float Specular[] = {1.0,1.0,1.0,1.0};
   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
   //  Light color and direction
   float Position[]  = {0.0,(float)(-0.43*Cos(360*foy)),-1.0,0.0};
   glLightfv(GL_LIGHT0,GL_POSITION,Position);

   //  Texture for this month
   glActiveTexture(GL_TEXTURE0);
   day[mo-1]->bind();
   //  Texture for next month
   glActiveTexture(GL_TEXTURE1);
   day[mo%12]->bind();
   //  Load nightime texture
   glActiveTexture(GL_TEXTURE2);
   night->bind();
   //  Load cloud, gloss and elevation texture
   glActiveTexture(GL_TEXTURE3);
   cge->bind();
   //  Reset texture unit
   glActiveTexture(GL_TEXTURE0);

   //  Enable shader
   shader[0]->bind();

   //  Set shader increments
   shader[0]->setUniformValue("mode",mode);
   shader[0]->setUniformValue("frac",frac);
   shader[0]->setUniformValue("DayTex0" ,0);
   shader[0]->setUniformValue("DayTex1" ,1);
   shader[0]->setUniformValue("NightTex",2);
   shader[0]->setUniformValue("CGETex"  ,3);

   //  Draw earth
   objects[0]->setRotate(zh,0,1,0);
   doScene();

   //  Enable shader
   shader[0]->release();
   //  Disable lighting
   glDisable(GL_LIGHTING);

   //  Draw axis
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3f(0,+1.2,0);
   glVertex3f(0,-1.2,0);
   glEnd();
}
