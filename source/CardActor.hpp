#ifndef CARDACTOR_HPP
#define CARDACTOR_HPP

#include "CardBuffer.hpp"
#include <QVector3D>

class CardActor
{
public:
    CardActor(CardBuffer& buffer);
    ~CardActor();

private:
    CardBuffer& _buffer;
    QVector3D _position;
};

#endif
