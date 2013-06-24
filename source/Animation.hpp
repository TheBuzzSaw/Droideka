#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class AnimationCollection;

class Animation
{
public:
    friend class AnimationCollection;

    Animation();
    Animation(const Animation& other);
    virtual ~Animation();

    Animation& operator=(const Animation& other);

    virtual bool update() = 0;

private:
    Animation* _nextAnimation;
    AnimationCollection* _collection;
};

#endif
