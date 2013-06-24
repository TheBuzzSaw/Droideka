#include "AnimationCollection.hpp"

AnimationCollection::AnimationCollection() : _firstAnimation(0)
{
}

AnimationCollection::~AnimationCollection()
{
    Animation* animation = _firstAnimation;

    while (animation)
    {
        Animation* nextAnimation = animation->_nextAnimation;
        animation->_nextAnimation = 0;
        animation->_collection = 0;
        animation = nextAnimation;
    }
}

void AnimationCollection::add(Animation& animation)
{
    if (!animation._collection)
    {
        animation._collection = this;
        animation._nextAnimation = _firstAnimation;
        _firstAnimation = &animation;
    }
}

void AnimationCollection::updateAll()
{
    Animation** a = &_firstAnimation;

    while (Animation* animation = *a)
    {
        if (animation->update())
        {
            a = &animation->_nextAnimation;
        }
        else
        {
            *a = animation->_nextAnimation;
            animation->_nextAnimation = 0;
            animation->_collection = 0;
        }
    }
}
