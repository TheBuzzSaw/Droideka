#include <QtGui/QApplication>
#include "LoginWindow.h"
#include "WidgetTestOpenGL.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetTestOpenGL w;
    w.show();
    
    return a.exec();
}
