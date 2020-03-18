#ifndef EX11V_H
#define EX11V_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "ex11opengl.h"

class Ex11viewer : public QWidget
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
   Ex11opengl*  ogl;
private slots:
   void lmove();        //  Light movement
public:
    Ex11viewer();
};

#endif
