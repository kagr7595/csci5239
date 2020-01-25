//
//  OpenGL Ex03opengl Widget
//

#ifndef EX03OPENGL_H
#define EX03OPENGL_H

#include "CUgl.h"

class Ex03opengl : public CUgl
{
Q_OBJECT
private:
   float x0,y0; // Model center
   float z0;    // Zoom level
public:
   Ex03opengl(QWidget* parent=0);                  // Constructor
   QSize sizeHint() const {return QSize(400,400);} // Default size of widget
public slots:
    void setX(double X);     // Set Model X position
    void setY(double Y);     // Set Model Y position
    void setZoom(double Z);  // Set Zoom level
signals:
    void zoom(QString text); // Zoom level
protected:
    void initializeGL();     // Initialize widget
    void paintGL();          // Draw widget
};

#endif
