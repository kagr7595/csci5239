#ifndef EX16V_H
#define EX16V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "ex16opengl.h"

class Ex16viewer : public QWidget
{
Q_OBJECT
private:
   QSlider*     Lpos;
   QSlider*     Zpos;
   QPushButton* light;
   Ex16opengl*  ogl;
private slots:
   void lmove();        //  Light movement
public:
    Ex16viewer();
};

#endif
