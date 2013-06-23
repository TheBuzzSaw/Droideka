#include "SpinnyAnimation.hpp"

SpinnyAnimation::SpinnyAnimation(CardActor& cardActor) : _cardActor(cardActor)
{
    _isSpinning = true;
}

SpinnyAnimation::~SpinnyAnimation()
{
}

bool SpinnyAnimation::update()
{
    _cardActor.rotation(_cardActor.rotation() + Rotation::fromDegrees(1.0f));
    //_cardActor.flip(_cardActor.flip() + Rotation::fromDegrees(1.0f));
    return _isSpinning;
}
