#ifndef CARDPILE_HPP
#define CARDPILE_HPP

#include "Card.hpp"
#include "../CardActor.hpp"
#include <QVector>

class CardPile
{
public:
    CardPile();
    ~CardPile();

private:
    CardPile(const CardPile& other);
    CardPile& operator=(const CardPile& other);

    QVector<Card*> _cards;
};

#endif
