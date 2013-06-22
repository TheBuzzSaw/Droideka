#include "CardSpecifications.hpp"

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
    const float Minimum = 1.0f;
    _width = Minimum < w ? w : Minimum;
}

void CardSpecifications::height(float h)
{
    const float Minimum = 1.0f;
    _height = Minimum < h ? h : Minimum;
}

void CardSpecifications::depth(float d)
{
    const float Minimum = 0.01f;
    _depth = Minimum < d ? d : Minimum;

}

void CardSpecifications::cornerRadius(float cr)
{
    const float Minimum = 0.01f;
    _cornerRadius = Minimum < cr ? cr : Minimum;
}

void CardSpecifications::cornerDetail(int cd)
{
    const int Minimum = 1;
    _cornerDetail = Minimum < cd ? cd : Minimum;
}
