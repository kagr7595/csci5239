#ifndef EX20V_H
#define EX20V_H

#include "ex20opengl.h"

class Ex20viewer : public QWidget
{
Q_OBJECT
private:
   Ex20opengl*  ogl;
public:
    Ex20viewer();
};

#endif
