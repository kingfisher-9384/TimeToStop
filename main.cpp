#include "mainwindow.hh"

#include <QApplication>
#include <QDir>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set working directory to the executable's folder
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    MainWindow w;
    w.show();
    return a.exec();
}
