//  Main Window class

#ifndef EX18MAIN_H
#define EX18MAIN_H

#include <QMainWindow>

class QLineEdit;
class Ex18opengl;

class Ex18main : public QMainWindow
{
Q_OBJECT
private:
   QString     file;
   Ex18opengl* ogl;
private slots:
   void open();
   void about();
private:
   QString readSettings();
   void writeSettings();
   void loadFile(QString name);
protected:
   void closeEvent(QCloseEvent* event);
public:
   Ex18main(QString argv="");
};

#endif
