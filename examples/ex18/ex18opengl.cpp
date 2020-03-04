//
//  OpenGL widget
//
#define GL_GLEXT_PROTOTYPES
#include "ex18opengl.h"
#include <QTextStream>

//
//  Constructor
//
Ex18opengl::Ex18opengl(QWidget* parent)
    : QOpenGLWidget(parent)
{
   W = H = 0;
   N = 0;
   wrapping = true;
   framebuf[0] = NULL;
   framebuf[1] = NULL;
   //  Set timer interval to 1ms
   timer.setInterval(0);
   connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
   timer.start();
}

//
//  Reset view
//
void Ex18opengl::pause(int on)
{
   if (on)
      timer.stop();
   else
      timer.start();
}

//
//  Set world wrap
//
void Ex18opengl::setWrap(bool on)
{
   wrapping = on;
   textureProperties();
}

//
//  Save application settings
//
void Ex18opengl::writeSettings(QSettings& settings)
{
   settings.setValue("wrap",wrapping);
}

//
//  Restore application settings
//
void Ex18opengl::readSettings(QSettings& settings)
{
   wrapping = settings.value("wrap",true).toBool();
}

//
//  Reset view
//
void Ex18opengl::reset()
{
   N = 0;
   //  Request redisplay
   update();
}

//
//  Initialize
//
void Ex18opengl::initializeGL()
{
   //  Load shader
   shader = new QOpenGLShaderProgram;
   //  Fragment shader
   if (!shader->addShaderFromSourceFile(QOpenGLShader::Fragment,":/ex18.frag"))
      Fatal("Error compiling ex18.frag\n"+shader->log());
   //  Link
   if (!shader->link())
      Fatal("Error linking shader\n"+shader->log());
}

//
//  Draw the window
//
void Ex18opengl::resizeGL(int w,int h)
{
   W = w*devicePixelRatio();
   H = h*devicePixelRatio();
   glViewport(0,0,W,H);
   //  Framebuffer
   N = 0;
   //  Set texture properties
   for (int k=0;k<2;k++)
   {
      if (framebuf[k]) delete framebuf[k];
      framebuf[k] = new QOpenGLFramebufferObject(w,h);
   }
   //  Set texture properties
   textureProperties();
}

//
//  Set texture properties
//
void Ex18opengl::textureProperties()
{
   makeCurrent();
   for (int k=0;k<2;k++)
      if (framebuf[k])
      {
      
         //  Nearest returns exact cell values
         glBindTexture(GL_TEXTURE_2D,framebuf[k]->texture());
         glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
         //  Wrap to create circular universe
         glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wrapping?GL_REPEAT:GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapping?GL_REPEAT:GL_CLAMP_TO_EDGE);
      }
}

//
//  Draw the window
//
void Ex18opengl::paintGL()
{
   //  Select output buffer
   int out = N%2;
   framebuf[out]->bind();
   //  Set initial pattern
   if (N==0)
   {
      //  Clear screen and set color
      glClearColor(0,0,0,0);
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3f(1,0,0);
      //  Initialize pattern
      initPattern();
   }
   //
   //  Compute next generation
   //
   else
   {
      framebuf[out]->bind();
      //  Enable shader
      shader->bind();
      //  Set offsets
      float dX = 1.0/W;
      float dY = 1.0/H;
      shader->setUniformValue("dX",dX);
      shader->setUniformValue("dY",dY);
      shader->setUniformValue("img",0);

      //  Source framebuffer
      glBindTexture(GL_TEXTURE_2D,framebuf[1-out]->texture());

      //  Compute generation
      glClear(GL_COLOR_BUFFER_BIT);
      glEnable(GL_TEXTURE_2D);
      glBegin(GL_QUADS);
      glTexCoord2f(0,0); glVertex2f(-1,-1);
      glTexCoord2f(0,1); glVertex2f(-1,+1);
      glTexCoord2f(1,1); glVertex2f(+1,+1);
      glTexCoord2f(1,0); glVertex2f(+1,-1);
      glEnd();
      glDisable(GL_TEXTURE_2D);

      //  Done with shader
      shader->release();
   }

   //  Blit to screen
   framebuf[out]->release();
   glBindTexture(GL_TEXTURE_2D,framebuf[out]->texture());
   glClear(GL_COLOR_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex2f(-1,-1);
   glTexCoord2f(0,1); glVertex2f(-1,+1);
   glTexCoord2f(1,1); glVertex2f(+1,+1);
   glTexCoord2f(1,0); glVertex2f(+1,-1);
   glEnd();
   glDisable(GL_TEXTURE_2D);

   //  Increment generations and display
   N++;
   //  This is reall slow so limit to every 100 generations
   if (N%100==0) emit generation("Generation "+QString::number(N));
}

//
//  Throw a fatal error and die
//
void Ex18opengl::Fatal(QString message)
{
   QMessageBox::critical(this,"Ex18",message);
   QApplication::quit();
}

//
//  Load file
//
QString Ex18opengl::loadFile(QString file)
{
   //  Open file
   QFile f(file);
   if (!f.open(QIODevice::ReadOnly)) return "Cannot open file "+file;
   QTextStream in(&f);
   QString line = in.readLine();
   //  Skip header
   while (line[0] == '#')
   {
      line = in.readLine();
   }
   //  Process header line
   line = line.simplified();
   line.replace(" ","");
   QStringList words = line.split(",");
   if (words.length()<3)
     return "Invalid header line "+line;
   else if (!words[0].startsWith("x="))
     return "Missing x= "+line;
   else if (!words[1].startsWith("y="))
     return "Missing y= "+line;
   else if (!words[2].startsWith("rule="))
     return "Missing rule= "+line;
   else if (words[2].mid(5) != "B3/S23")
     return "Only rule B3/S23 implemented,  "+words[2].mid(5)+" not supported.";
   dx = words[0].mid(2).toInt();
   dy = words[1].mid(2).toInt();
   //  Read pattern
   pattern = "";
   while (!in.atEnd())
   {
      pattern += in.readLine();
   }
   //  Remove whitespace
   pattern = pattern.simplified();
   pattern.replace(" ", "");
   //  Reset simulation
   N = 0;
   return "";
}

//
//  Load file
//
void Ex18opengl::initPattern()
{
   //  Center pattern
   int x = (dx<W) ? (W-dx)/2 : 0;
   int y = H-1-(dy<H ? (H-dy)/2 : 0);
   int x0 = x;
   //  Generate pattern
   int k = 0;
   for (int i=0;i<pattern.length();i++)
   {
      //  Live cell(s)
      if (pattern[i]=='o')
      {
         //  k==0 => one
         if (k<=0) k = 1;
         //  Draw k live cells in a row
         for (;k>0;k--)
         {
            GLubyte dot[] = {0xFF};
            glWindowPos2i(x++,y);
            glBitmap(1,1,0,0,0,0,dot);
         }
      }
      //  Dead cell(s)
      else if (pattern[i]=='b')
      {
         x += (k?k:1);
         k = 0;
      }
      //  End of Line
      else if (pattern[i]=='$')
      {
         y -= (k?k:1);
         x = x0;
         k = 0;
      }
      //  Repeat count
      else if (pattern[i].isDigit())
         k = 10*k + pattern[i].digitValue();
      //  End of patterm
      else if (pattern[i] == '!')
         break;
   }
}
