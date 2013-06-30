#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "MainWidget.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    virtual ~MainWindow();

protected:
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void contextMenuEvent(QContextMenuEvent* event);

private:
    void toggleFullscreen();

    MainWidget* _mainWidget;
    bool _isFullscreen;
};

#endif
