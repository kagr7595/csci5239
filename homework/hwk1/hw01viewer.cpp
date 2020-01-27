//
//  Hw01viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "hw01viewer.h"
#include "hw01opengl.h"

//
//  Constructor
//
Hw01viewer::Hw01viewer()
{
   //  Set window title
   setWindowTitle(tr("Assignment Hw01: NDC to RGB shader - Kathy Grimes"));

   //  Create new OpenGL widget
   Hw01opengl* ogl = new Hw01opengl;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("None");
   shader->addItem("NDC to RGB Shader");

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

   //  Lighting
   QCheckBox* lighting = new QCheckBox("");

   //  View angle
   QLabel* angles = new QLabel();

   int max_pos = 10;
   int init_pos = 0;
   //  Horizontal Slider X
   QSlider* slider_x = new QSlider(Qt::Horizontal);
   slider_x->setRange(-max_pos, max_pos);
   slider_x->setSliderPosition(init_pos);

   //  Horizontal Slider Y
   QSlider* slider_y = new QSlider(Qt::Horizontal);
   slider_y->setRange(-max_pos, max_pos);
   slider_y->setSliderPosition(init_pos);

   //  Horizontal Slider Z
   QSlider* slider_z = new QSlider(Qt::Horizontal);
   slider_z->setRange(-max_pos, max_pos);
   slider_z->setSliderPosition(init_pos);

   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,7,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Projection"),1,1);
   layout->addWidget(projection,1,2);
   layout->addWidget(new QLabel("Object"),2,1);
   layout->addWidget(object,2,2);
   layout->addWidget(new QLabel("X"),3,1);
   layout->addWidget(slider_x,3,2);
   layout->addWidget(new QLabel("Y"),4,1);
   layout->addWidget(slider_y,4,2);
   layout->addWidget(new QLabel("Z"),5,1);
   layout->addWidget(slider_z,5,2);
   layout->addWidget(new QLabel("Lighting"),6,1);
   layout->addWidget(lighting,6,2);
   layout->addWidget(new QLabel("Angles"),7,1);
   layout->addWidget(angles,7,2);
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
   connect(slider_x, SIGNAL(valueChanged(int))         , ogl,SLOT(set_x(int)));
   connect(slider_y, SIGNAL(valueChanged(int))         , ogl,SLOT(set_y(int)));
   connect(slider_z, SIGNAL(valueChanged(int))         , ogl,SLOT(set_z(int)));
   connect(lighting,SIGNAL(stateChanged(int))          , ogl,SLOT(setLighting(int)));
   //  Connect angles() signal to label
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}
