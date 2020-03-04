//
//  Ex12viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QCamera>
#include "ex12viewer.h"
#include "ex12frame.h"

//
//  Constructor
//
Ex12viewer::Ex12viewer()
{
   //  Set window title
   setWindowTitle(tr("Ex12:  Image Processing"));

   //  Create new OpenGL widget
   Ex12opengl* ogl = new Ex12opengl;

   //  Create new camera and frame widgets
   QCamera* camera = new QCamera;
   Ex12frame* frame = new Ex12frame;
// camera->setCaptureMode(QCamera::CaptureStillImage);
   camera->setViewfinder(frame);
   connect(frame,SIGNAL(frameAvailable(QImage)), ogl,SLOT(setImage(QImage)));
   camera->start();

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("None");
   shader->addItem("Copy");
   shader->addItem("Sharpen");
   shader->addItem("Blur");
   shader->addItem("Erosion");
   shader->addItem("Dilation");
   shader->addItem("Laplacian");
   shader->addItem("Prewitt");
   shader->addItem("Sobel");

   //  Select number of passes
   QSpinBox* passes = new QSpinBox();
   passes->setRange(1,20);

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,4,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Passes"),1,1);
   layout->addWidget(passes,1,2);
   layout->addWidget(rst,3,1);
   layout->addWidget(quit,3,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(2,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int))    , ogl,SLOT(setShader(int)));
   connect(passes,SIGNAL(valueChanged(int))           , ogl,SLOT(setPasses(int)));
   //  Connect reset() and lmove() signals
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}
