#ifndef SPINNYANIMATION_HPP
#define SPINNYANIMATION_HPP

#include "Animation.hpp"
#include "CardActor.hpp"

class SpinnyAnimation : public Animation
{
public:
    SpinnyAnimation();
    virtual ~SpinnyAnimation();

    inline void set(CardActor* cardActor) { _cardActor = cardActor; }
    inline void set(const Rotation rotation) { _rotation = rotation; }

    virtual bool update();
    inline void stop() { _isSpinning = false; }

private:
    CardActor* _cardActor;
    Rotation _rotation;
    bool _isSpinning;
};

#endif
