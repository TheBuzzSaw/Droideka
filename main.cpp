#include <QtGui/QApplication>
#include "LoginWindow.h"
#include "WindowTestOpenGL.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LoginWindow w;
    //WindowTestOpenGL w;
    WidgetTestOpenGL w;
    w.show();
    
    return a.exec();
}
