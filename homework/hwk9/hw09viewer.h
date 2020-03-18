#ifndef HW09V_H
#define HW09V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "hw09opengl.h"

class Hw09viewer : public QWidget
{
Q_OBJECT
private:
   QSlider*     Lpos;
   QSlider*     Zpos;
   QSlider*     R;
   QSlider*     G;
   QSlider*     B;
   QPushButton* light;
   QCheckBox* c;
   QCheckBox* m;
   QCheckBox* y;
   QCheckBox* k;
   QCheckBox* gs;
   QButtonGroup* bg;
   Hw09opengl*  ogl;
private slots:
   void lmove();        //  Light movement
public:
    Hw09viewer();
};

#endif
