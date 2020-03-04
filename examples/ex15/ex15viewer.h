#ifndef EX15V_H
#define EX15V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "ex15opengl.h"

class Ex15viewer : public QWidget
{
Q_OBJECT
private:
   QSlider*     Lpos;
   QSlider*     Zpos;
   QPushButton* light;
   Ex15opengl*  ogl;
public:
    Ex15viewer();
};

#endif
