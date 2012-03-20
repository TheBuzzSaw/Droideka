#include "MainWindow.hpp"
#include <QtGui>
#include <QKeyEvent>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mGLW = new CanvasOpenGL(this);
    setCentralWidget(mGLW);

    setWindowTitle(QString("Droideka"));
    resize(QSize(640, 480));

    setupMenu();
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

void MainWindow::setupMenu()
{
    setupActions();

    mHelpMenu = menuBar()->addMenu("Help");
    mHelpMenu->addAction(mAboutQtAct);
}

void MainWindow::setupActions()
{
    mAboutQtAct = new QAction("&About Qt", this);
    mAboutQtAct->setStatusTip("Information about Qt");
    connect(mAboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
