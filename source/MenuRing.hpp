#ifndef MENURING_HPP
#define MENURING_HPP

#include <QObject>
#include <QAction>
#include <QPoint>
#include "Rotation.hpp"

class MenuRing : public QObject
{
    Q_OBJECT
public:
    explicit MenuRing(QObject* parent = 0);
    virtual ~MenuRing();

    static bool tryGetAngle(QPoint direction, int minDistance,
        Rotation& rotation);

signals:

public slots:

};

#endif
