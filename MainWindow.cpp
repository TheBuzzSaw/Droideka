#include "MainWindow.hpp"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mGLW = new WidgetTestOpenGL(this);
    setCentralWidget(mGLW);

    setWindowTitle(QString("Droideka"));
    resize(QSize(640, 480));
}

void MainWindow::keyPressEvent(QKeyEvent* inEvent)
{
    switch (inEvent->key())
    {

    case Qt::Key_Escape:
        close();
        break;

    default:
        break;
    }
}
