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
    case Qt::Key_Escape:
        close();
        break;

    case Qt::Key_Space:
        _mainWidget->dump();
        break;

    default:
        break;
    }

    if (event->key() == Qt::Key_Escape)
        close();
}
