//
//  OpenGL Hw03opengl Widget
//

#ifndef HW03OPENGL_H
#define HW03OPENGL_H

#include "CUgl.h"

class Hw03opengl : public CUgl
{
Q_OBJECT
private:
   float x0,y0; // Model center
   int t0;
public:
   Hw03opengl(QWidget* parent=0);                  // Constructor
   QSize sizeHint() const {return QSize(400,400);} // Default size of widget
public slots:
    void setX(double X);     // Set Model X position
    void setY(double Y);     // Set Model Y position
signals:
    void zoom(QString text); // Zoom level
    void fps(QString);    // Frames per second
protected:
    void initializeGL();     // Initialize widget
    void paintGL();          // Draw widget
};

#endif
