#include <QtGui/QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //WidgetTestOpenGL w;
    //LoginWindow x;
    w.show();
    //x.show();
    
    return a.exec();
}
