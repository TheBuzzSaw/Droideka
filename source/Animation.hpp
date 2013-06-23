#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class Animation
{
public:
    friend class AnimationCollection;

    Animation();
    Animation(const Animation& other);
    virtual ~Animation();

    virtual bool update() = 0;

private:
    Animation* _nextAnimation;
    void* _collection;
};

#endif
