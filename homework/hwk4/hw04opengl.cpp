//
//  OpenGL widget
//
#include "hw04opengl.h"

//
//  Constructor
//
Hw04opengl::Hw04opengl(QWidget* parent)
    : CUgl(parent)
{
}

//
//  Cube Vertexes
//
const int cube_size=36;
const float cube_data[] =  // Vertex data
{
//  X  Y  Z  W   Nx Ny Nz    R G B   s t
   //  Front
   +1,+1,+1,+1,   0, 0,+1,   1,0,0,  1,1,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,  1,0,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,  1,0,
   -1,-1,+1,+1,   0, 0,+1,   1,0,0,  0,0,
   //  Back
   -1,-1,-1,+1,   0, 0,-1,   0,0,1,  1,0,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,  1,1,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,  1,1,
   +1,+1,-1,+1,   0, 0,-1,   0,0,1,  0,1,
   //  Right
   +1,+1,+1,+1,  +1, 0, 0,   1,1,0,  0,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,  1,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,  1,1,
   +1,-1,-1,+1,  +1, 0, 0,   1,1,0,  1,0,
   //  Left
   -1,+1,+1,+1,  -1, 0, 0,   0,1,0,  1,1,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,  1,0,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,  1,0,
   -1,-1,-1,+1,  -1, 0, 0,   0,1,0,  0,0,
   //  Top
   +1,+1,+1,+1,   0,+1, 0,   0,1,1,  1,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,  0,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,  0,0,
   -1,+1,-1,+1,   0,+1, 0,   0,1,1,  0,1,
   //  Bottom
   -1,-1,-1,+1,   0,-1, 0,   1,0,1,  0,0,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,  0,1,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,  0,1,
   +1,-1,+1,+1,   0,-1, 0,   1,0,1,  1,1,
   };

//
//  Initialize
//
void Hw04opengl::initializeGL()
{
   // Texture
   tex = new QOpenGLTexture(QImage(":/crate.png").mirrored());

   //  Load shaders
   addShader(":/hw04.vert",":/hw04.frag");

   //  Cube vertex buffer object
   //  Copy data to vertex buffer object
   cube_buffer.create();
   cube_buffer.bind();
   cube_buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
   cube_buffer.allocate(sizeof(cube_data));
   cube_buffer.write(0,cube_data,sizeof(cube_data));
   //  Unbind this buffer
   cube_buffer.release();
}

//
//  Draw the window
//
void Hw04opengl::paintGL()
{
   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   //  Set projection for fixed pipeline
   doModelViewProjection();

   //  Set light
   QVector3D lpos = doLight();
   Q_UNUSED(lpos);  // Suppress warning since lpos is not used yet

   //  Fixed pipeline
   if (mode==0)
   {
      //  Enable textures
      glEnable(GL_TEXTURE_2D);
      tex->bind();

      //  Enabe arrays
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);

      //  Set pointers
      
      glVertexPointer  (4,GL_FLOAT,12*sizeof(GLfloat),cube_data);
      glNormalPointer  (  GL_FLOAT,12*sizeof(GLfloat),cube_data+4);
      glColorPointer   (3,GL_FLOAT,12*sizeof(GLfloat),cube_data+7);
      glTexCoordPointer(2,GL_FLOAT,12*sizeof(GLfloat),cube_data+10);

      //  Draw the cube slightly offset
      glPushMatrix();
      glTranslated(0,0,0.5);
      glDrawArrays(GL_TRIANGLES,0,cube_size);
      glPopMatrix();

      //  Disable arrays
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisableClientState(GL_NORMAL_ARRAY);
      glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);

      //  Disable textures and lighting
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_LIGHTING);
   }
   //  OpenGL 4 style shaders
   else
   {
     //  Create Projection matrix
      QMatrix4x4 proj;
      proj.setToIdentity();
      float asp = width() / (float)height();
      if (fov)
         proj.perspective(fov,asp,dim/4,4*dim);
      else
         proj.ortho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
      //  Create View matrix
      QMatrix4x4 view;
      if (fov) view.translate(0,0,-2*dim);
      view.rotate(ph,1,0,0);
      view.rotate(th,0,1,0);
      //  Create ModelView matrix
      QMatrix4x4 mv = view;
      mv.translate(0,0,0.5);

      // Enable shader
      shader[mode]->bind();
      //  Set Modelview and Projection Matrix
      shader[mode]->setUniformValue("ProjectionMatrix",proj);
      shader[mode]->setUniformValue("ModelViewMatrix",mv);

      //  Select cube buffer
      cube_buffer.bind();
      //   Attribute 0: vertex coordinate (vec4) at offset 0
      shader[mode]->enableAttributeArray(0);
      shader[mode]->setAttributeBuffer(0,GL_FLOAT,0,4,12*sizeof(float));
      //   Attribute 1:  vertex color (vec3) offset 7 floats
      shader[mode]->enableAttributeArray(1);
      shader[mode]->setAttributeBuffer(1,GL_FLOAT,7*sizeof(float),3,12*sizeof(float));

      // Draw the cube
      glDrawArrays(GL_TRIANGLES,0,cube_size);

      //  Disable vertex arrays
      shader[mode]->disableAttributeArray(0);
      shader[mode]->disableAttributeArray(1);

      //  Unbind this buffer
      cube_buffer.release();

      // Back to fixed pipeline
      shader[mode]->release();
   }

   //  Axes for reference
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3f(0,0,0);
   glVertex3f(2,0,0);
   glVertex3f(0,0,0);
   glVertex3f(0,2,0);
   glVertex3f(0,0,0);
   glVertex3f(0,0,2);
   glEnd();
}
