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
    if (event->key() == Qt::Key_Escape)
        close();
}
