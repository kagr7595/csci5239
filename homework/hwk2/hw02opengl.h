//
//  OpenGL Hw02opengl Widget
//

#ifndef HW02OPENGL_H
#define HW02OPENGL_H

#include "CUgl.h"

class Hw02opengl : public CUgl
{
Q_OBJECT
private:
   float x0,y0; // Model center
public:
   Hw02opengl(QWidget* parent=0);                  // Constructor
   QSize sizeHint() const {return QSize(400,400);} // Default size of widget
public slots:
    void setX(double X);     // Set Model X position
    void setY(double Y);     // Set Model Y position
signals:
    void zoom(QString text); // Zoom level
protected:
    void initializeGL();     // Initialize widget
    void paintGL();          // Draw widget
};

#endif
