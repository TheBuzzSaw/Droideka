#include "CardModule.hpp"

CardModule::CardModule(QGLWidget* inWidget) : mWidget(inWidget)
{
}

CardModule::~CardModule()
{
}

void CardModule::onPulse()
{
}

void CardModule::onResize(int inWidth, int inHeight)
{
    (void)inWidth;
    (void)inHeight;
}

void CardModule::onDraw()
{
}

void CardModule::onMousePress(QMouseEvent* inEvent)
{
    (void)inEvent;
}

void CardModule::onMouseMove(QMouseEvent* inEvent)
{
    (void)inEvent;
}
