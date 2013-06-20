#include "MainWindow.hpp"
#include <QHBoxLayout>

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
