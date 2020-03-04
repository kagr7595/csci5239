//
//  OpenGL Ex15opengl Widget
//

#ifndef EX15OPENGL_H
#define EX15OPENGL_H

#include "CUgl.h"

class Ex15opengl : public CUgl
{
Q_OBJECT
private:
   int     mode;            //  Mode
   float   pct;             //  Position
   QOpenGLTexture* day[12]; //  Day textures
   QOpenGLTexture* night;   //  Night texture
   QOpenGLTexture* cge;     //  Cloud/Gloss/Elevation
public:
   Ex15opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
    void setMode(int m);                   //  Slot mode
    void setPos(int pct);                  //  Slot to set position
signals:
    void datim(QString text);              //  Signal for date and time
protected:
    void initializeGL();                   //  Initialize widget
    void paintGL();                        //  Draw widget
};

#endif
