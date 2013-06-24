#include "Card.hpp"

Card::Card(GLuint frontTexture, GLuint backTexture)
    : _frontTexture(frontTexture),
    _backTexture(backTexture)
{
}

Card::Card(const Card& other)
    : _frontTexture(other._frontTexture),
    _backTexture(other._backTexture)
{
}

Card::~Card()
{
}

Card& Card::operator=(const Card& other)
{
    _frontTexture = other._frontTexture;
    _backTexture = other._backTexture;
    return *this;
}
