//
//  Ex20viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "ex20viewer.h"

//
//  Constructor
//
Ex20viewer::Ex20viewer()
{
   //  Set window title
   setWindowTitle(tr("Ex20: nBody Simulator"));

   //  Create new OpenGL widget
   ogl = new Ex20opengl;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("Sequential");
   shader->addItem("OpenMP");
   shader->addItem("Geometry");

   //  View angle and zoom
   QLabel* fps    = new QLabel();
   QLabel* angles = new QLabel();

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,5,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("FPS"),1,1);
   layout->addWidget(fps,1,2);
   layout->addWidget(new QLabel("Angles"),2,1);
   layout->addWidget(angles,2,2);
   layout->addWidget(rst,4,1);
   layout->addWidget(quit,4,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(3,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int))     , ogl,SLOT(setMode(int)));
   //  Connect angles() and zoom() signal to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   connect(ogl,SIGNAL(FPS(QString))    , fps,SLOT(setText(QString)));
   //  Connect reset() and lmove() signals
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}
