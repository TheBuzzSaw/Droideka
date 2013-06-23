#ifndef ANIMATIONCOLLECTION_HPP
#define ANIMATIONCOLLECTION_HPP

#include "Animation.hpp"

class AnimationCollection
{
public:
    AnimationCollection();
    ~AnimationCollection();

    void add(Animation& animation);
    void updateAll();

private:
    Animation* _firstAnimation;
};

#endif
