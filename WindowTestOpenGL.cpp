#include "WindowTestOpenGL.hpp"
#include <QtOpenGL>

WindowTestOpenGL::WindowTestOpenGL()
{
    mGLW = new WidgetTestOpenGL(this);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(mGLW);
    setLayout(layout);
    resize(QSize(400, 400));
    setWindowTitle(tr("Droideka"));
}

void WindowTestOpenGL::keyPressEvent(QKeyEvent* inEvent)
{
    if (inEvent->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(inEvent);
}
