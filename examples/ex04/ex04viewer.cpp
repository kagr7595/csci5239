//
//  Ex04viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "ex04viewer.h"

//
//  Constructor
//
Ex04viewer::Ex04viewer()
{
   //  Set window title
   setWindowTitle(tr("Ex04:  Lighting"));

   //  Create new OpenGL widget
   ogl = new Ex04opengl;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("None");
   shader->addItem("Stored");
   shader->addItem("Vertex Blinn");
   shader->addItem("Vertex Phong");
   shader->addItem("Pixel Blinn");
   shader->addItem("Pixel Phong");

   //  Select projection
   QComboBox* projection = new QComboBox();
   projection->addItem("Orthogonal");
   projection->addItem("Perspective");

   //  Select object
   QComboBox* object = new QComboBox();
   object->addItem("Cube");
   object->addItem("Icosahedron");
   object->addItem("Teapot");
   object->addItem("Cruiser");

   //  Center position
   Lpos = new QSlider(Qt::Horizontal);
   Zpos = new QSlider(Qt::Horizontal);
   Lpos->setRange(0,360);
   Zpos->setRange(-100,100);

   //  View angle and zoom
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
   layout->addWidget(ogl,0,0,9,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Projection"),1,1);
   layout->addWidget(projection,1,2);
   layout->addWidget(new QLabel("Object"),2,1);
   layout->addWidget(object,2,2);
   layout->addWidget(new QLabel("Light Position"),3,1);
   layout->addWidget(Lpos,3,2);
   layout->addWidget(new QLabel("Light Elevation"),4,1);
   layout->addWidget(Zpos,4,2);
   layout->addWidget(new QLabel("Light"),5,1);
   layout->addWidget(light,5,2);
   layout->addWidget(new QLabel("Angles"),6,1);
   layout->addWidget(angles,6,2);
   layout->addWidget(new QLabel("FPS"),7,1);
   layout->addWidget(frames,7,2);
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
   connect(Lpos,SIGNAL(valueChanged(int)) , ogl,SLOT(setLightAngle(int)));
   connect(Zpos,SIGNAL(valueChanged(int)) , ogl,SLOT(setLightElevation(int)));
   //  Connect angles() and zoom() signal to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   connect(ogl,SIGNAL(fps(QString))    , frames,SLOT(setText(QString)));
   connect(ogl,SIGNAL(light(int))      , Lpos,SLOT(setValue(int)));
   //  Connect reset() and lmove() signals
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   connect(light,SIGNAL(pressed()),this,SLOT(lmove()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));

   //  Settings
   Zpos->setValue(100);
   projection->setCurrentIndex(1);
}

//
//  Light pause/move
//
void Ex04viewer::lmove()
{
   bool pause = (light->text()=="Pause");
   if (pause)
      light->setText("Animate");
   else
      light->setText("Pause");
   ogl->setLightMove(!pause);
}
