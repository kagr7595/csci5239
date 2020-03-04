#include <QtGui>
#include "ex18main.h"
#include "ex18opengl.h"

//
//  Constructor
//
Ex18main::Ex18main(QString file)
{
   //  Create tabs
   ogl = new Ex18opengl;
   setCentralWidget(ogl);

   //  Create File Actions
   QAction* openAct = new QAction("&Open...", this);
   openAct->setShortcuts(QKeySequence::Open);
   openAct->setStatusTip(tr("Open an RLE file"));
   connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

   QAction* exitAct = new QAction("E&xit", this);
   exitAct->setShortcuts(QKeySequence::Quit);
   exitAct->setStatusTip("Exit the application");
   connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

   //  Create Simulation Actions
   QAction* resetAct = new QAction("&Restart", this);
   resetAct->setStatusTip(tr("Restart Simulation"));
   connect(resetAct, SIGNAL(triggered()), ogl , SLOT(reset()));

   QAction* wrapAct = new QAction("&World Wrap", this);
   wrapAct->setStatusTip(tr("Wrap Simulation World"));
   wrapAct->setCheckable(true);
   connect(wrapAct, SIGNAL(toggled(bool)), ogl , SLOT(setWrap(bool)));

   //  Create Help Actions
   QAction* aboutAct = new QAction("&About", this);
   aboutAct->setStatusTip("Show the application's About box");
   connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

   QAction* aboutQtAct = new QAction("About &Qt", this);
   aboutQtAct->setStatusTip("Show the Qt library's About box");
   connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    //  Create File menu
   QMenu* fileMenu = menuBar()->addMenu("&File");
   fileMenu->addAction(openAct);
   fileMenu->addAction(exitAct);

   //  Create Simulation menu
   QMenu* simMenu = menuBar()->addMenu("&Simulation");
   simMenu->addAction(resetAct);
   simMenu->addAction(wrapAct);

   //  Create Help menu
   menuBar()->addSeparator();
   QMenu* helpMenu = menuBar()->addMenu("&Help");
   helpMenu->addAction(aboutAct);
   helpMenu->addAction(aboutQtAct);

   //  Initialize status bar
   statusBar()->showMessage("Ready");
   connect(ogl, SIGNAL(generation(QString)), statusBar() , SLOT(showMessage(QString)));

   //  OS specific properties
   setUnifiedTitleAndToolBarOnMac(true);

   //  Restore settings (returns file name)
   QString name = readSettings();
   if (!file.isEmpty()) name = file;
   wrapAct->setChecked(ogl->wrap());

   //  Read inputs
   loadFile(name);
}

//
//  Load inputs from file
//
void Ex18main::loadFile(QString name)
{
   //  Load pattern
   QString err = ogl->loadFile(name);
   //  Flag error
   if (!err.isEmpty())
   {
      QMessageBox::warning(this,"Ex18",err);
      return;
   }
   //  Set current RLE file name
   else
   {
      file = name;
      setWindowFilePath(name);
   }
}

//
//  File Open slot
//
void Ex18main::open()
{
   ogl->pause(1);
   QString name = QFileDialog::getOpenFileName(this,"Open File",".","rle Files (*.rle)");
   if (!name.isEmpty()) loadFile(name);
   ogl->pause(0);
}

//
//  Help About slot
//
void Ex18main::about()
{
   QMessageBox::about(this, "About Ex18",
              "Conway's Game of Life using a shader");
}

//
//  Trap window close event
//
void Ex18main::closeEvent(QCloseEvent *event)
{
   //  Save settings
   writeSettings();
   event->accept();
}

//
//  Save application settings
//
void Ex18main::writeSettings()
{
   QSettings settings("CSCI","Ex18");
   settings.setValue("file",file);
   settings.setValue("pos",pos());
   settings.setValue("size",size());
   ogl->writeSettings(settings);
}

//
//  Restore application settings
//
QString Ex18main::readSettings()
{
   QSettings settings("CSCI","Ex18");
   QString file = settings.value("file",QString("vacuum-cleaner.rle")).toString();
   QPoint  pos  = settings.value("pos",QPoint(200,200)).toPoint();
   QSize   size = settings.value("size",QSize(800,800)).toSize();
   resize(size);
   move(pos);
   ogl->readSettings(settings);
   return file;
}
