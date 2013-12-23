#include "MenuRing.hpp"
#include <QtGlobal>
#include <QtMath>
#include <QDebug>

MenuRing::MenuRing(QObject* parent) :
    QObject(parent)
{
}

MenuRing::~MenuRing()
{
}

bool MenuRing::tryGetAngle(QPoint direction, int minDistance,
    Rotation& rotation)
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
        const qreal Pi = 3.1415926535897932384626433832795028841971;
        const qreal HalfPi = Pi / qreal(2);

        qDebug() << Pi << HalfPi;

        if (direction.y() == 0)
        {
            radians = direction.x() > 0 ? HalfPi : -HalfPi;
        }
        else
        {
            qreal ratio = qreal(direction.x()) / qreal(direction.y());

            radians = qAtan(ratio);

            if (direction.y() > 0)
            {
                qreal bottom = direction.x() > 0 ? Pi : -Pi;
                radians = bottom - radians;
            }
            else
            {
                radians = -radians;
            }
        }

        rotation = Rotation::fromRadians(radians);
    }

    return result;
}
