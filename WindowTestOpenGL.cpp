#include "WindowTestOpenGL.hpp"
#include <QtOpenGL>

WindowTestOpenGL::WindowTestOpenGL()
{
    mGLW = new WidgetTestOpenGL;

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(mGLW);
    setLayout(layout);
    resize(QSize(400, 400));
}

void WindowTestOpenGL::keyPressEvent(QKeyEvent* inEvent)
{
    if (inEvent->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(inEvent);
}
