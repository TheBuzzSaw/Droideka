#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "CanvasOpenGL.hpp"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    virtual void onKeyPress(QKeyEvent* inEvent);

private slots:
    void showAboutDialog();

private:
    void setupActions();
    void setupMenu();
    void toggleFullscreen();

    CanvasOpenGL* mCanvas;
    QMenu* mHelpMenu;
    QAction* mAboutAct;
    QAction* mAboutQtAct;
    bool mIsFullScreen;
};

#endif
