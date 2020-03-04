//
//  Ex14viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "ex14viewer.h"

//
//  Constructor
//
Ex14viewer::Ex14viewer()
{
   //  Set window title
   setWindowTitle(tr("Ex14:  Find the Teapot"));

   //  Create new OpenGL widget
   Ex14opengl* ogl = new Ex14opengl;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("Reference Image");
   shader->addItem("Test Image Image");
   shader->addItem("Convolution");

   //  Select Shape
   QComboBox* shape = new QComboBox();
   shape->addItem("Triangle");
   shape->addItem("Square");
   shape->addItem("Diamond");
   shape->addItem("Circle");
   shape->addItem("Teapot");

   //  Select Size
   QComboBox* size = new QComboBox();
   size->addItem("8");
   size->addItem("16");
   size->addItem("32");
   size->addItem("64");
   size->addItem("128");
   size->addItem("256");

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,5,1);
   layout->addWidget(new QLabel("Mode"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Shape"),1,1);
   layout->addWidget(shape,1,2);
   layout->addWidget(new QLabel("Size"),2,1);
   layout->addWidget(size,2,2);
   layout->addWidget(rst,4,1);
   layout->addWidget(quit,4,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(2,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int)) , ogl,SLOT(setShader(int)));
   connect(shape ,SIGNAL(currentIndexChanged(int)) , ogl,SLOT(setShape(int)));
   connect(size  ,SIGNAL(currentIndexChanged(int)) , ogl,SLOT(setSize(int)));
   //  Connect reset() and lmove() signals
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}
