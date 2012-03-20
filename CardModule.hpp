#ifndef CARDMODULE_HPP
#define CARDMODULE_HPP

#include "Matrix4x4.hpp"
#include <QGLWidget>
#include <QMouseEvent>

class CardModule
{
public:
    CardModule(QGLWidget* inWidget);
    virtual ~CardModule();

    virtual void onPulse();
    virtual void onResize(int inWidth, int inHeight);
    virtual void onDraw();
    virtual void onMousePress(QMouseEvent* inEvent);
    virtual void onMouseMove(QMouseEvent* inEvent);

private:
    QGLWidget* mWidget;
};

#endif
