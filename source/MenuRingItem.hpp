#ifndef MENURINGITEM_HPP
#define MENURINGITEM_HPP

#include <QtCore>
#include <QObject>
#include <QOpenGLFunctions>
#include "BasicProgram.hpp"

class MenuRingItem : public QObject
{
    Q_OBJECT
public:
    MenuRingItem(QString name);
    virtual ~MenuRingItem();

    void draw(BasicProgram& program);

    QString name() const;

    void select();

signals:
    void selected();

private:
    QString _name;
    GLuint _texture;
};

#endif
