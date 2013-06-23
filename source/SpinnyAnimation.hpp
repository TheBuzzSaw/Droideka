#ifndef SPINNYANIMATION_HPP
#define SPINNYANIMATION_HPP

#include "Animation.hpp"
#include "CardActor.hpp"

class SpinnyAnimation : public Animation
{
public:
    SpinnyAnimation(CardActor& cardActor);
    virtual ~SpinnyAnimation();

    virtual bool update();
    inline void stop() { _isSpinning = false; }

private:
    CardActor& _cardActor;
    bool _isSpinning;
};

#endif
