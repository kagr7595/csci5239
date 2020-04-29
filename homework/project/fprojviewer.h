#ifndef FProjV_H
#define FProjV_H

#include <QWidget>
#include <QSlider>
#include <QDoubleSpinBox>
#include "fprojopengl.h"

class Fprojviewer : public QWidget
{
Q_OBJECT
private:
   QSlider*     Vpos;
   QSlider*     Lpos;
   QSlider*     Lrad;
   QSlider*     Zpos;
   QPushButton* light;
   QPushButton* day;
   Fprojopengl*  ogl;
private slots:
   void lmove();        //  Light movement
public:
    Fprojviewer();
};

#endif
