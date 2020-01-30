#ifndef HW02V_H
#define HW02V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "hw02opengl.h"

class Hw02viewer : public QWidget
{
Q_OBJECT
private:
   QDoubleSpinBox* Xpos;
   QDoubleSpinBox* Ypos;
   QPushButton*    light;
   Hw02opengl*     ogl;
private slots:
   void reset();        //  Reset angles
   void lmove();        //  Pause/animate light
public:
    Hw02viewer();
};

#endif
