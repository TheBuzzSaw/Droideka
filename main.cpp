#include <QtGui/QApplication>
#include "LoginWindow.h"
#include "WidgetTestOpenGL.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetTestOpenGL w;
    //LoginWindow x;
    w.show();
    //x.show();
    
    return a.exec();
}
