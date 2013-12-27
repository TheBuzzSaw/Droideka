#include "MenuRingItem.hpp"
#include <QImage>
#include <QFont>
#include <QGLContext>

MenuRingItem::MenuRingItem(QString name)
    : QObject(nullptr)
    , _name(std::move(name))
{
    initializeOpenGLFunctions();

    QFont font("../DejaVuSans.ttf");
    font.setPixelSize(64);
    QImage image(256, 128, QImage::Format_ARGB32);
    image.fill(QColor(0, 0, 0, 0));

    QPainter painter(&image);
    painter.setFont(font);
    painter.setPen(Qt::green);
    painter.drawText(image.rect(), Qt::AlignCenter, _name);

    //_texture = QGLContext::currentContext()->bindTexture(image);
}

MenuRingItem::~MenuRingItem()
{
    //QGLContext::currentContext()->deleteTexture(_texture);
}

void MenuRingItem::draw(BasicProgram& program)
{
    program.enableTexture(true);
    program.setHighlight(QVector4D());
    glBindTexture(GL_TEXTURE_2D, _texture);

}

QString MenuRingItem::name() const
{
    return _name;
}

void MenuRingItem::select()
{
    emit selected();
}
