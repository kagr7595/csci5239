//
//  OpenGL Ex17opengl Widget
//

#ifndef EX17OPENGL_H
#define EX17OPENGL_H

#include "CUgl.h"

class Ex17opengl : public CUgl
{
Q_OBJECT
private:
   int mode;  // Noise type
public:
   Ex17opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
   void setMode(int m); // Set noise type
protected:
   void initializeGL(); //  Initialize widget
   void paintGL();      //  Draw widget
};

#endif
