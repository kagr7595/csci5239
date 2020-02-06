//
//  Icosahedron class
//  The constructor sets the position, size and rotation
//  All parameters are assigned default values
//
#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H

#include "Object.h"

class Icosahedron: public Object
{
private:
   float sx,sy,sz;  //  Dimensions in X/Y/Z directions
public:
   Icosahedron(const QString tex="");          //  Constructor
   void setScale(float dx,float dy,float dz);  //  Set scale
   void display();                             //  Render the icosahedron
};

#endif
