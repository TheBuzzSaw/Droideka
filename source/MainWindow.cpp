#include "MainWindow.hpp"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
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
