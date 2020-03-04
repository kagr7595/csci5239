//
//  OpenGL Ex16opengl Widget
//

#ifndef EX16OPENGL_H
#define EX16OPENGL_H

#include "CUgl.h"

class Ex16opengl : public CUgl
{
Q_OBJECT
public:
   Ex16opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
protected:
   void initializeGL(); //  Initialize widget
   void paintGL();      //  Draw widget
};

#endif
