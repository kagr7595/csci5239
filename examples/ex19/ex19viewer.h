#ifndef EX19V_H
#define EX19V_H

#include "ex19opengl.h"

class Ex19viewer : public QWidget
{
Q_OBJECT
private:
   Ex19opengl*  ogl;
public:
    Ex19viewer();
};

#endif
