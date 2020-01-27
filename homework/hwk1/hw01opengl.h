//
//  OpenGL Hw01opengl Widget
//

#ifndef HW01OPENGL_H
#define HW01OPENGL_H

#include <QtOpenGL>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QElapsedTimer>
#include "Object.h"

class Hw01opengl : public QOpenGLWidget
{
Q_OBJECT
private:
   bool    light;     //  Lighting
   int     mode;      //  Display mode
   int     th,ph;     //  Display angles
   bool    mouse;     //  Mouse pressed
   QPoint  pos;       //  Mouse position
   int     fov;       //  Field of view
   double  dim;       //  Display size
   double  asp;       //  Sceen aspect ratio
   int     x_pos;     //  x_pos of object
   int     y_pos;     //  y_pos of object
   int     z_pos;     //  z_pos of object
   Object* obj;       //  Object
   QTimer           timer;       //  Timer for animations
   QElapsedTimer    time;        //  Track elapsed time
   QOpenGLShaderProgram shader;  //  Shader
   QVector<Object*> objects;     //  Objects
public:
   Hw01opengl(QWidget* parent=0);                  //  Constructor
   QSize sizeHint() const {return QSize(400,400);} //  Default size of widget
public slots:
    void setShader(int on);                //  Slot to set shader
    void set_x(int x);                     //  Slider to set x value
    void set_y(int y);                     //  Slider to set y value
    void set_z(int z);                     //  Slider to set z value
    void setPerspective(int on);           //  Slot to set projection type
    void setObject(int type);              //  Slot to set displayed object
    void setLighting(int on);              //  Slot to set lighting
signals:
    void angles(QString text);             //  Signal for view angles
protected:
    void initializeGL();                   //  Initialize widget
    void resizeGL(int width, int height);  //  Resize widget
    void paintGL();                        //  Draw widget
    void mousePressEvent(QMouseEvent*);    //  Mouse pressed
    void mouseReleaseEvent(QMouseEvent*);  //  Mouse released
    void mouseMoveEvent(QMouseEvent*);     //  Mouse moved
    void wheelEvent(QWheelEvent*);         //  Mouse wheel
private:
   void Fatal(QString message);            //  Error handler
   void Projection();                      //  Update projection
};

#endif
