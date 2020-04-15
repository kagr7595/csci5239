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
   QSlider*     Lpos;
   QSlider*     Zpos;
   QPushButton* light;
   Fprojopengl*  ogl;
private slots:
   void lmove();        //  Light movement
public:
    Fprojviewer();
};

#endif
