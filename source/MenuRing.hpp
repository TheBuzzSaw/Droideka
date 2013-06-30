#ifndef MENURING_HPP
#define MENURING_HPP

#include <QObject>
#include <QAction>

class MenuRing : public QObject
{
    Q_OBJECT
public:
    explicit MenuRing(QObject* parent = 0);
    virtual ~MenuRing();

signals:

public slots:

};

#endif
