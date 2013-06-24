#include "SpinnyAnimation.hpp"

SpinnyAnimation::SpinnyAnimation() : _cardActor(0)
{
    _isSpinning = true;
}

SpinnyAnimation::~SpinnyAnimation()
{
}

bool SpinnyAnimation::update()
{
    bool result = false;

    if (_cardActor)
    {
        _isSpinning = qrand() % 1000;

        _cardActor->rotation(_cardActor->rotation() + _rotation);
        result = _isSpinning;
    }

    return result;
}
