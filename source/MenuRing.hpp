#ifndef MENURING_HPP
#define MENURING_HPP

#include <QObject>
#include <QAction>
#include <QPoint>
#include <QOpenGLFunctions>
#include <QVector>
#include "Rotation.hpp"

class MenuRing : public QObject
{
    Q_OBJECT
public:
    explicit MenuRing(QObject* parent = 0);
    virtual ~MenuRing();

    void add(QString option);

    static bool tryGetAngle(QPoint direction, int minDistance,
        Rotation& rotation);

signals:

public slots:

private:
    QOpenGLFunctions _functions;
    QVector<QString> _options;
};

#endif
