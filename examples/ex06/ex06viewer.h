#ifndef EX06V_H
#define EX06V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "ex06opengl.h"

class Ex06viewer : public QWidget
{
Q_OBJECT
private:
   QSlider*     Lpos;
   QSlider*     Zpos;
   QPushButton* light;
   Ex06opengl*  ogl;
private slots:
   void lmove();        //  Light movement
public:
    Ex06viewer();
};

#endif
