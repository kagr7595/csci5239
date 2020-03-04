//
//  OpenGL Ex18opengl Widget
//

#ifndef EX18OPENGL_H
#define EX18OPENGL_H

#include <QtOpenGL>

class Ex18opengl : public QOpenGLWidget
{
Q_OBJECT
private:
   int    W,H;      //  World dimensions
   int    N;        //  Generations
   int    dx,dy;    //  Pattern size
   bool   wrapping; //  World wrapping
   QString pattern; //  Pattern string
   QTimer timer;    //  Timer for animation
   QOpenGLFramebufferObject* framebuf[2]; //  Framebuffers
   QOpenGLShaderProgram*     shader;      // Shader
public:
   Ex18opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(800,800);} //  Default size of widget
   void readSettings(QSettings&);                  //  Read simulation settings
   void writeSettings(QSettings&);                 //  Write simulation settings
   bool wrap() {return wrapping;}                  //  World wrapping
public slots:
   void reset();                    //  Reset simulation
   void setWrap(bool);              //  Wrap world
   void pause(int);                 //  Pause simulation
   QString loadFile(QString file);  //  Load pattern from file
signals:
   void generation(QString txt);    //  Report generation
protected:
   void initializeGL();        //  Initialize widget
   void resizeGL(int w,int h); //  Size widget
   void paintGL();             //  Draw widget
private:
   void Fatal(QString err);    //  Throw fatal error
   void initPattern();         //  Set pattern image
   void textureProperties();   //  Set texture properties
};

#endif
