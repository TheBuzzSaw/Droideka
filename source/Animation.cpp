#include "Animation.hpp"

Animation::Animation() : _nextAnimation(0), _collection(0)
{
}

Animation::Animation(const Animation& other) : _nextAnimation(0),
    _collection(0)
{
    (void)other;
}

Animation::~Animation()
{
}

Animation& Animation::operator=(const Animation& other)
{
    (void)other;
    return *this;
}
