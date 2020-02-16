#ifndef HW04V_H
#define HW04V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "hw04opengl.h"

class Hw04viewer : public QWidget
{
Q_OBJECT
private:
   QSlider*     Lpos;
   QSlider*     Zpos;
   QPushButton* light;
   Hw04opengl*  ogl;
private slots:
   void lmove();        //  Light movement
public:
    Hw04viewer();
};

#endif
