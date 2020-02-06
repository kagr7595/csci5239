#ifndef HW03V_H
#define HW03V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "hw03opengl.h"

class Hw03viewer : public QWidget
{
Q_OBJECT
private:
   QDoubleSpinBox* Xpos;
   QDoubleSpinBox* Ypos;
   QPushButton*    light;
   Hw03opengl*     ogl;
private slots:
   void reset();        //  Reset angles
   void lmove();        //  Pause/animate light
public:
    Hw03viewer();
};

#endif
