#include "CardSpecifications.hpp"
#include <QtGlobal>

CardSpecifications::CardSpecifications()
{
    _width = 6.3f;
    _height = 8.8f;
    _depth = 0.05f;
    _cornerRadius = 0.25f;
    _cornerDetail = 4;
}

CardSpecifications::CardSpecifications(const CardSpecifications &other)
{
    _width = other._width;
    _height = other._height;
    _depth = other._depth;
    _cornerRadius = other._cornerRadius;
    _cornerDetail = other._cornerDetail;
}

CardSpecifications::~CardSpecifications()
{
}

void CardSpecifications::width(float w)
{
    _width = qMax(w, 1.0f);
}

void CardSpecifications::height(float h)
{
    _height = qMax(h, 1.0f);
}

void CardSpecifications::depth(float d)
{
    _depth = qMax(d, 0.01f);
}

void CardSpecifications::cornerRadius(float cr)
{
    _cornerRadius = qMax(cr, 0.01f);
}

void CardSpecifications::cornerDetail(int cd)
{
    _cornerDetail = qMax(cd, 1);
}
