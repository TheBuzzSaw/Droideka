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

    mIsFullScreen = false;
}

void MainWindow::keyPressEvent(QKeyEvent* inEvent)
{
    switch (inEvent->key())
    {
    case Qt::Key_F11:
        toggleFullscreen();
        break;

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
    mHelpMenu->addAction(mAboutAct);

    statusBar();
}

void MainWindow::setupActions()
{
    mAboutAct = new QAction("About &DEJARIX", this);
    mAboutAct->setStatusTip("Information about DEJARIX");
    connect(mAboutAct, SIGNAL(triggered()), this, SLOT(showAboutDialog()));

    mAboutQtAct = new QAction("About &Qt", this);
    mAboutQtAct->setStatusTip("Information about Qt");
    connect(mAboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::showAboutDialog()
{
    QMessageBox::about(this, QString("About DEJARIX"),
        QString("DEJARIX 0.1 -- Star Wars CCG Online"));
}

void MainWindow::toggleFullscreen()
{
    mIsFullScreen = !mIsFullScreen;

    if (mIsFullScreen)
        showFullScreen();
    else
        showNormal();
}
