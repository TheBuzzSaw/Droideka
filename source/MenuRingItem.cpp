#include "MenuRingItem.hpp"
#include <QImage>
#include <QFont>

MenuRingItem::MenuRingItem(QString name)
    : QObject(nullptr)
    , _name(std::move(name))
{
    initializeOpenGLFunctions();
    QImage image(256, 256, QImage::Format_ARGB32);
}

MenuRingItem::~MenuRingItem()
{
}

QString MenuRingItem::name() const
{
    return _name;
}

void MenuRingItem::select()
{
    emit selected();
}
