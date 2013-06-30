#ifndef LOCATIONPOPPER_HPP
#define LOCATIONPOPPER_HPP

#include "../CardActor.hpp"

class LocationPopper
{
public:
    LocationPopper();
    ~LocationPopper();

    void set(CardActor* firstActor, CardActor* secondActor);
    void clear();

private:
    struct
    {
        CardActor* actor;
        QVector3D oldPosition;
    } _actors[2];
};

#endif
