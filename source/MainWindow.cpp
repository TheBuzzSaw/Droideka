#include "MainWindow.hpp"
#include <QKeyEvent>
#include <QDir>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
#ifdef Q_OS_MAC
    qDebug() << QDir::currentPath();
    QDir::setCurrent("../../..");
    qDebug() << QDir::currentPath();
#endif

    _mainWidget = new MainWidget(this);
    _isFullscreen = false;

    setCentralWidget(_mainWidget);
    setWindowTitle("DEJARIX");
    resize(800, 600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_F11:
        toggleFullscreen();
        break;

    case Qt::Key_Escape:
        close();
        break;

    case Qt::Key_Space:
        _mainWidget->dump();
        break;

    default:
        break;
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    (void)event;
    //qDebug() << "context";
}

void MainWindow::toggleFullscreen()
{
    _isFullscreen = !_isFullscreen;

    if (_isFullscreen)
    {
        showFullScreen();
    }
    else
    {
        showNormal();
    }
}
