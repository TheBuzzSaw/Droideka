#include "MenuRing.hpp"
#include <QtGlobal>
#include <QtMath>

MenuRing::MenuRing(QObject* parent)
    : QObject(parent)
    , _functions(QOpenGLContext::currentContext())
{
}

MenuRing::~MenuRing()
{
}

void MenuRing::add(MenuRingItem* item)
{
    if (item)
    {
        item->setParent(this);
        _items.append(item);
    }
}

bool MenuRing::tryGetAngle(QPoint direction, int minDistance,
    RotationF& rotation)
{
    bool result = false;

    minDistance = qMax(minDistance, 1);
    int minDistanceSquared = minDistance * minDistance;
    int distanceSquared = direction.x() * direction.x()
        + direction.y() * direction.y();

    if (distanceSquared >= minDistanceSquared)
    {
        result = true;

        qreal radians = 0;

        if (direction.y() == 0)
        {
            radians = direction.x() > 0 ? halfPi<qreal>() : -halfPi<qreal>();
        }
        else
        {
            qreal ratio = qreal(direction.x()) / qreal(direction.y());

            radians = qAtan(ratio);

            if (direction.y() > 0)
            {
                qreal bottom = direction.x() > 0 ? pi<qreal>() : -pi<qreal>();
                radians = bottom - radians;
            }
            else
            {
                radians = -radians;
            }
        }

        rotation = RotationF::fromRadians(radians);
    }

    return result;
}
