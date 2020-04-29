//
//  CU OpenGL Widget
//

#ifndef CUGL_H
#define CUGL_H

#include <QtOpenGL>
#include <QString>
#include <QVector>
#include "Object.h"

#define SUMMER 0
#define WINTER 1
#define SPRING 2
#define FALL 3
#define OTHER 4

#define BLACK 1
#define BROWN 2
#define RED 3
#define BLUE 4
#define GREEN 5
#define ORANGE 6
#define YELLOW 7
#define WHITE 8
#define NUM_COLORS 8

#define SKYBOX 0
#define FLOOR 1


class CUgl : public QOpenGLWidget
{
Q_OBJECT
private:
   float            La,Ld,Ls; // Light intensity
   float            Lr;       // Light radius
   float            ylight;   // Light elevation
   bool             move;     // Moving light
   int              obj;      // Selected Object
   QTimer           timer;    // Timer for animations
protected:
   QElapsedTimer    time;     // Track elapsed time
   QVector<Object*> objects;  // Objects
   bool             mouse;    // Mouse pressed
   QPoint           pos;      // Mouse position
   float            zh;       // Light angle
   int              fov;      // Field of view
   float            Dim;      // Default size
   float            dim;      // Display size
   int              th,ph;    // Display angles
   int              mode;     // Selected shader
   int              season;     // Selected season
   QVector<QOpenGLShaderProgram*> shader[2]; // Shaders
public:
   CUgl(QWidget* parent=0);        // Constructor
   QSize sizeHint() const {return QSize(400,400);} // Default size of widget
public slots:
   void reset();
   void setDim(float d);                            // Set scene size
   void setPerspective(int on);                     // Set perspective
   void setShader(int sel);                         // Set shader
   void setObject(int type);                        // Set season
   void setLightMove(bool on);                      // Set light animation
   void setLightAngle(int th);                      // Set light angle
   void setLightElevation(int pct);                 // Set light elevation (percent)
   void setLightRad(int dist);                      // Set light radius
   void setLightIntensity(float a,float d,float s); // Set light intensity
   void maxFPS(bool);                               // Set max fps
   void addShader(int pshader, QString vert,QString frag,QString names=""); // Add shader
   void addShader3(int pshader, QString vert,QString geom,QString frag);    // Add shader
protected:
   void initializeGL();                             // Initialization
   void mousePressEvent(QMouseEvent*);              // Mouse pressed
   void mouseReleaseEvent(QMouseEvent*);            // Mouse released
   void mouseMoveEvent(QMouseEvent*);               // Mouse moved
   void wheelEvent(QWheelEvent*);                   // Mouse wheel
   void Fatal(QString message);                     // Error handler
   QVector3D doLight();                             // Enable light
   void doModelViewProjection();                    // Apply projection
   void doOrtho(int w,int h,float zoom=1,float dx=0,float dy=0); // Apply orthographic projection with zoom and pan
   float getTime() {return 0.001*time.elapsed();}   // Elapsed time in seconds
   QOpenGLTexture* loadImage(const QString file);   // Method to load texture
private slots:
   void tick();                                     // Method to capture timer ticks
signals:
   void light(int angle);                           // Signal for light angle
   void angles(QString text);                       // Signal for view angles
};

#endif
