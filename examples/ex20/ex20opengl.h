//
//  OpenGL Ex20opengl Widget
//

#ifndef EX20OPENGL_H
#define EX20OPENGL_H

#include "CUgl.h"

//  Star Structure
typedef struct
{
   float x,y,z;  //  Position
   float u,v,w;  //  Velocity
   float r,g,b;  //  Color
}  Star;

class Ex20opengl : public CUgl
{
Q_OBJECT
private:
   int     N;           //  Star count
   int     src,dst;     //  Source and destination
   float   vel;         //  Initial velocity
   int     frame;       //  Frames per second
   int     t0;          //  Seconds
   Star*   stars;       //  Vertices
   QOpenGLTexture* tex; //  Texture
public:
   Ex20opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
    void setMode(int m);                   //  Slot to set mode
signals:
    void FPS(QString text);                //  Signal for fps
protected:
    void initializeGL();                   //  Initialize widget
    void paintGL();                        //  Draw widget
private:
   void Move(int k);
   void Step();
   void InitLoc();
};

#endif
