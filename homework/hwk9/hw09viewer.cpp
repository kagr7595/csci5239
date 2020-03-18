//
//  Hw09viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "hw09viewer.h"

//
//  Constructor
//
Hw09viewer::Hw09viewer()
{
   //  Set window title
   setWindowTitle(tr("Hw7:  Image Processing - Kathy Grimes"));

   //  Create new OpenGL widget
   ogl = new Hw09opengl;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("None");
   shader->addItem("Emboss Color/Grayscale");
   shader->addItem("Grayscale CMYK");
   shader->addItem("Grayscale RGB");

   //  Select number of passes
   QSpinBox* passes = new QSpinBox();
   passes->setRange(1,20);

   //  Select projection
   QComboBox* projection = new QComboBox();
   projection->addItem("Orthogonal");
   projection->addItem("Perspective");
   projection->setCurrentIndex(0);

   //  Center position
   Lpos = new QSlider(Qt::Horizontal);
   Zpos = new QSlider(Qt::Horizontal);
   Lpos->setRange(0,360);
   Zpos->setRange(-100,100);

   R = new QSlider(Qt::Horizontal);
   G = new QSlider(Qt::Horizontal);
   B = new QSlider(Qt::Horizontal);

   R->setRange(0,255);
   G->setRange(0,255);
   B->setRange(0,255);


   //  View angle and zoom
   QLabel* angles = new QLabel();

   //  Pause/resume button
   light = new QPushButton("Pause");

   QCheckBox* c = new QCheckBox();
   QCheckBox* m = new QCheckBox();
   QCheckBox* y = new QCheckBox();
   QCheckBox* k = new QCheckBox();
   c->setChecked(true);
   m->setChecked(false);
   y->setChecked(false);
   k->setChecked(false);
   QButtonGroup* bg = new QButtonGroup();
   bg->addButton(c);
   bg->addButton(m);
   bg->addButton(y);
   bg->addButton(k);
   QCheckBox* gs = new QCheckBox();
   gs->setChecked(false);

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,15,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   //layout->addWidget(new QLabel("Passes"),1,1);
   //layout->addWidget(passes,1,2);
   layout->addWidget(new QLabel("Projection"),1,1);
   layout->addWidget(projection,1,2);
   layout->addWidget(new QLabel("Light Position"),2,1);
   layout->addWidget(Lpos,2,2);
   layout->addWidget(new QLabel("Light Elevation"),3,1);
   layout->addWidget(Zpos,3,2);
   layout->addWidget(new QLabel("Light"),4,1);
   layout->addWidget(light,4,2);
   layout->addWidget(new QLabel("R"),6,1);
   layout->addWidget(R,6,2);
   layout->addWidget(new QLabel("G"),7,1);
   layout->addWidget(G,7,2);
   layout->addWidget(new QLabel("B"),8,1);
   layout->addWidget(B,8,2);
   layout->addWidget(new QLabel("C"),9,1);
   layout->addWidget(c,9,2);
   layout->addWidget(new QLabel("M"),10,1);
   layout->addWidget(m,10,2);
   layout->addWidget(new QLabel("Y"),11,1);
   layout->addWidget(y,11,2);
   layout->addWidget(new QLabel("K"),12,1);
   layout->addWidget(k,12,2);
   layout->addWidget(new QLabel("EmbossGray"),5,1);
   layout->addWidget(gs,5,2);
   layout->addWidget(new QLabel("Angles"),13,1);
   layout->addWidget(angles,13,2);
   layout->addWidget(rst,15,1);
   layout->addWidget(quit,15,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(15,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int))    , ogl,SLOT(setShader(int)));
   connect(passes,SIGNAL(valueChanged(int))           , ogl,SLOT(setPasses(int)));
   connect(projection,SIGNAL(currentIndexChanged(int)), ogl,SLOT(setPerspective(int)));
   connect(Lpos,SIGNAL(valueChanged(int)) , ogl,SLOT(setLightAngle(int)));
   connect(Zpos,SIGNAL(valueChanged(int)) , ogl,SLOT(setLightElevation(int)));
   connect(R,SIGNAL(valueChanged(int)) , ogl,SLOT(setR(int)));
   connect(G,SIGNAL(valueChanged(int)) , ogl,SLOT(setG(int)));
   connect(B,SIGNAL(valueChanged(int)) , ogl,SLOT(setB(int)));
   connect(c,SIGNAL(stateChanged(int)) , ogl,SLOT(setC(int)));
   connect(m,SIGNAL(stateChanged(int)) , ogl,SLOT(setM(int)));
   connect(y,SIGNAL(stateChanged(int)) , ogl,SLOT(setY(int)));
   connect(k,SIGNAL(stateChanged(int)) , ogl,SLOT(setK(int)));
   connect(gs,SIGNAL(stateChanged(int)) , ogl,SLOT(setGS(int)));
   //  Connect angles() and zoom() signal to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   connect(ogl,SIGNAL(light(int))      , Lpos,SLOT(setValue(int)));
   //  Connect reset() and lmove() signals
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   connect(light,SIGNAL(pressed()),this,SLOT(lmove()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));

   //  Light elevation
   Zpos->setValue(100);
   R->setValue(127);
   G->setValue(127);
   B->setValue(127);
}

//
//  Light pause/move
//
void Hw09viewer::lmove()
{
   bool pause = (light->text()=="Pause");
   if (pause)
      light->setText("Animate");
   else
      light->setText("Pause");
   ogl->setLightMove(!pause);
}
