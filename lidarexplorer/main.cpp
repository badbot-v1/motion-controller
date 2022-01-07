#include "mainwindow.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QApplication>
#include <sharedstorage/sharedstrings.hpp>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QFile f("./config/qdarkstyle/style.qss");
  if (!f.exists())   {
      printf("Unable to set stylesheet, file not found\n");
  }
  else   {
      f.open(QFile::ReadOnly | QFile::Text);
      QTextStream ts(&f);
      a.setStyleSheet(ts.readAll());
  }

  SharedStrings::get()->setVal("config-file", "./config/l2i.yml");

  MainWindow w;
  w.show();

  return a.exec();
}
