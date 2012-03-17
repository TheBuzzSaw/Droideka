#ifndef WINDOWTESTOPENGL_HPP
#define WINDOWTESTOPENGL_HPP

#include "WidgetTestOpenGL.hpp"
#include <QWidget>

class WindowTestOpenGL : public QWidget
{
    Q_OBJECT

public:
    WindowTestOpenGL();
    
signals:
    
public slots:

protected:
    virtual void keyPressEvent(QKeyEvent* inEvent);

private:
    WidgetTestOpenGL* mGLW;
};

#endif
