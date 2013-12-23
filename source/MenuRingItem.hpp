#ifndef MENURINGITEM_HPP
#define MENURINGITEM_HPP

#include <QtCore>
#include <QObject>
#include <QOpenGLFunctions>

class MenuRingItem : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    MenuRingItem(QString name);
    virtual ~MenuRingItem();

    QString name() const;

    void select();

signals:
    void selected();

private:
    QString _name;
};

#endif
