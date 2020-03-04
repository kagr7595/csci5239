//
//  OpenGL widget
//
#include "ex20opengl.h"
#include <math.h>

//
//  Advance time one time step for star k
//
void Ex20opengl::Move(int k)
{
   int k0 = k+src;
   int k1 = k+dst;
   float dt = 1e-3;
   int i;
   //  Calculate force components
   double a=0;
   double b=0;
   double c=0;
   for (i=src;i<src+N;i++)
   {
      double dx = stars[i].x-stars[k0].x;
      double dy = stars[i].y-stars[k0].y;
      double dz = stars[i].z-stars[k0].z;
      double d = sqrt(dx*dx+dy*dy+dz*dz)+1;  // Add 1 to d to dampen movement
      double f = 1/(d*d*d);                  // Normalize and scale to 1/r^2
      a += f*dx;
      b += f*dy;
      c += f*dz;
   }
   //  Update velocity
   stars[k1].u = stars[k0].u + dt*a;
   stars[k1].v = stars[k0].v + dt*b;
   stars[k1].w = stars[k0].w + dt*c;
   //  Update position
   stars[k1].x = stars[k0].x + dt*stars[k1].u;
   stars[k1].y = stars[k0].y + dt*stars[k1].v;
   stars[k1].z = stars[k0].z + dt*stars[k1].w;
}

//
//  Advance time one time step
//
void Ex20opengl::Step()
{
   int k;
   //  Switch source and destination
   src = src?0:N;
   dst = dst?0:N;
   //  OpenMP
   if (mode)
      #pragma omp parallel for
      for (k=0;k<N;k++)
         Move(k);
   //  Sequential
   else
      for (k=0;k<N;k++)
         Move(k);
}

//
//  Scaled random value
//
void rand3(float Sx,float Sy,float Sz,float& X,float& Y,float& Z)
{
   float x = 0;
   float y = 0;
   float z = 0;
   float d = 2;
   while (d>1)
   {
      x = rand()/(0.5*RAND_MAX)-1;
      y = rand()/(0.5*RAND_MAX)-1;
      z = rand()/(0.5*RAND_MAX)-1;
      d = x*x+y*y+z*z;
   }
   X = Sx*x;
   Y = Sy*y;
   Z = Sz*z;
}

//
//  Initialize nBody problem
//
void Ex20opengl::InitLoc()
{
   //  Allocate room for twice as many bodies to facilitate ping-pong
   if (!stars) stars = (Star*)malloc(2*N*sizeof(Star));
   if (!stars) Fatal("Error allocating memory for stars\n");
   src = N;
   dst = 0;
   //  Assign random locations
   for (int k=0;k<N;k++)
   {
      rand3(dim/2,dim/2,dim/3,stars[k].x,stars[k].y,stars[k].z);
      rand3(vel,vel,vel,stars[k].u,stars[k].v,stars[k].w);
      switch (k%3)
      {
         case 0:
           stars[k].r = 1.0;
           stars[k].g = 1.0;
           stars[k].b = 1.0;
           break;
         case 1:
           stars[k].r = 1.0;
           stars[k].g = 0.9;
           stars[k].b = 0.5;
           break;
         case 2:
           stars[k].r = 0.5;
           stars[k].g = 0.9;
           stars[k].b = 1.0;
           break;
      }
      stars[k+N].r = stars[k].r;
      stars[k+N].g = stars[k].g;
      stars[k+N].b = stars[k].b;
   }
}

//
//  Constructor
//
Ex20opengl::Ex20opengl(QWidget* parent)
    : CUgl(parent,false)
{
   mode  = 0;
   frame = 0;
   stars = 0;
   N = 2048;
   InitLoc();
}

//
//  Set mode
//
void Ex20opengl::setMode(int m)
{
   mode = m;
   //  Request redisplay
   update();
}

//
//  Initialize
//
void Ex20opengl::initializeGL()
{
   //  Load shaders
   addShader3(":/ex20.vert",":/ex20.geom",":/ex20.frag");

   //  Load smoke particle
   tex = loadImage(":/star.png");

   // Set maximum fps
   maxFPS(1);
}

//
//  Draw the window
//
void Ex20opengl::paintGL()
{
   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT);

   //  Apply projection
   doModelViewProjection();

   //  Integrate
   Step();

   //  Set textures
   tex->bind();

   //  Apply shader
   if (mode==2)
   {
      shader[0]->bind();
      shader[0]->setUniformValue("star",0);
      shader[0]->setUniformValue("size",0.1f);
      glBlendFunc(GL_ONE,GL_ONE);
      glEnable(GL_BLEND);
   }

   //  Draw stars using vertex arrays
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glVertexPointer(3,GL_FLOAT,sizeof(Star),&stars[0].x);
   glColorPointer(3,GL_FLOAT,sizeof(Star),&stars[0].r);
   //  Draw all stars from dst count N
   glDrawArrays(GL_POINTS,dst,N);
   //  Disable vertex arrays
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);

   //  Unset shader
   if (mode==2)
   {
      shader[0]->release();
      glDisable(GL_BLEND);
   }

   //  Frame counter
   frame++;
   int t = time.elapsed()/1000;
   if (t>t0)
   {
      emit FPS(QString::number(frame));
      t0 = t;
      frame = 0;
   }
}
