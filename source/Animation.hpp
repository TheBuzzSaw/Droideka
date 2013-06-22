#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class Animation
{
public:
    Animation();
    virtual ~Animation();

    virtual bool update() = 0;

private:
    Animation* _nextAnimation;
};

#endif
