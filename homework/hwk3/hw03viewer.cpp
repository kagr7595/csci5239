//
//  Hw03viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "hw03viewer.h"

//
//  Constructor
//
Hw03viewer::Hw03viewer()
{
   //  Set window title
   setWindowTitle(tr("Assignment HW03:  Performance - Kathy Grimes"));

   //  Create new OpenGL widget
   ogl = new Hw03opengl;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("None");
   shader->addItem("Switch, Offset, & Stripes");
   shader->addItem("FragIFSwitch, Offset, & Stripes");
   shader->addItem("FragFUNCSwitch, Offset, & Stripes");
   shader->addItem("VertIFSwitch, Offset, & Stripes");
   shader->addItem("VertFUNCSwitch, Offset, & Stripes");
   shader->addItem("Light up strobe XY");
   shader->addItem("FragIFLight up strobe XY");
   shader->addItem("FragFUNCLight up strobe XY");
   shader->addItem("VertIFLight up strobe XY");
   shader->addItem("VertFUNCLight up strobe XY");

   //  Select projection
   QComboBox* projection = new QComboBox();
   projection->addItem("Orthogonal");
   projection->addItem("Perspective");

   //  Select object
   QComboBox* object = new QComboBox();
   object->addItem("Cube");
   object->addItem("Icosahedron");
   object->addItem("Teapot");
   object->addItem("Suzanne");

   //  Center position
   Xpos = new QDoubleSpinBox();
   Ypos = new QDoubleSpinBox();
   Xpos->setRange(-100,100);Xpos->setDecimals(6);Xpos->setSingleStep(0.1);Xpos->setValue(1);
   Ypos->setRange(-100,100);Ypos->setDecimals(6);Ypos->setSingleStep(0.1);

   //  View angle
   QLabel* angles = new QLabel();
   //  Frames per second
   QLabel* frames = new QLabel();

   //  Pause/resume button
   light = new QPushButton("Pause");

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,11,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Projection"),1,1);
   layout->addWidget(projection,1,2);
   layout->addWidget(new QLabel("Object"),2,1);
   layout->addWidget(object,2,2);
   layout->addWidget(new QLabel("X Position"),3,1);
   layout->addWidget(Xpos,3,2);
   layout->addWidget(new QLabel("Y Position"),4,1);
   layout->addWidget(Ypos,4,2);
   layout->addWidget(new QLabel("Angles"),5,1);
   layout->addWidget(angles,5,2);
   layout->addWidget(new QLabel("FPS"),6,1);
   layout->addWidget(frames,6,2);
   layout->addWidget(new QLabel("Light"),7,1);
   layout->addWidget(light,7,2);
   layout->addWidget(rst,9,1);
   layout->addWidget(quit,9,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(8,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int))     , ogl,SLOT(setShader(int)));
   connect(object,SIGNAL(currentIndexChanged(int))     , ogl,SLOT(setObject(int)));
   connect(projection,SIGNAL(currentIndexChanged(int)) , ogl,SLOT(setPerspective(int)));
   connect(Xpos,SIGNAL(valueChanged(double)) , ogl,SLOT(setX(double)));
   connect(Ypos,SIGNAL(valueChanged(double)) , ogl,SLOT(setY(double)));
   //  Connect angles() to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   //  Connect fps() to labels
   connect(ogl,SIGNAL(fps(QString))    , frames,SLOT(setText(QString)));
   //  Connect reset() and lmove() signals
   connect(rst  ,SIGNAL(pressed()),this,SLOT(reset()));
   connect(light,SIGNAL(pressed()),this,SLOT(lmove()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));

   //  Settings
   projection->setCurrentIndex(1);
}

//
//  Reset view
//
void Hw03viewer::reset()
{
   Xpos->setValue(1);
   Ypos->setValue(0);
   ogl->reset();
}


//
//  Light pause/move
//
void Hw03viewer::lmove()
{
   bool pause = (light->text()=="Pause");
   if (pause)
      light->setText("Animate");
   else
      light->setText("Pause");
   ogl->setLightMove(!pause);
}
