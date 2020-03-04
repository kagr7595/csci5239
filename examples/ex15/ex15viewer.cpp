//
//  Ex15viewer Widget
//

#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include "ex15viewer.h"

//
//  Constructor
//
Ex15viewer::Ex15viewer()
{
   //  Set window title
   setWindowTitle(tr("Ex15:  Blue Marble"));

   //  Create new OpenGL widget
   ogl = new Ex15opengl;

   //  Select shader
   QComboBox* shader = new QComboBox();
   shader->addItem("Seasonal");
   shader->addItem("Diurnal");
   shader->addItem("Clouds");

   //  View angle and zoom
   QLabel* angles = new QLabel();
   QLabel* date = new QLabel();

   //  Slider
   QSlider* slider = new QSlider(Qt::Horizontal);
   slider->setRange(0,100);

   //  Reset
   QPushButton* rst = new QPushButton("Reset");
   //  Quit
   QPushButton* quit = new QPushButton("Quit");

   //  Set layout of child widgets
   QGridLayout* layout = new QGridLayout;
   layout->addWidget(ogl,0,0,6,1);
   layout->addWidget(new QLabel("Shader"),0,1);
   layout->addWidget(shader,0,2);
   layout->addWidget(new QLabel("Angles"),1,1);
   layout->addWidget(angles,1,2);
   layout->addWidget(new QLabel("Date"),2,1);
   layout->addWidget(date,2,2);
   layout->addWidget(new QLabel("Position"),3,1);
   layout->addWidget(slider,3,2);
   layout->addWidget(rst,5,1);
   layout->addWidget(quit,5,2);
   //  Manage resizing
   layout->setColumnStretch(0,100);
   layout->setColumnMinimumWidth(0,100);
   layout->setRowStretch(4,100);
   setLayout(layout);

   //  Connect valueChanged() signals to ogl
   connect(shader,SIGNAL(currentIndexChanged(int)), ogl,SLOT(setMode(int)));
   //  Connect angles() and zoom() signal to labels
   connect(ogl,SIGNAL(angles(QString)) , angles,SLOT(setText(QString)));
   connect(ogl,SIGNAL(datim(QString)) , date,SLOT(setText(QString)));
   //  Connect reset() signal
   connect(slider,SIGNAL(valueChanged(int)) , ogl,SLOT(setPos(int)));
   connect(rst  ,SIGNAL(pressed()),ogl,SLOT(reset()));
   //  Connect quit() signal to qApp::quit()
   connect(quit,SIGNAL(pressed()) , qApp,SLOT(quit()));
}
