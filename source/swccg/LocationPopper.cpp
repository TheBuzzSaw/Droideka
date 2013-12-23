#include "LocationPopper.hpp"

LocationPopper::LocationPopper()
{
    _actors[0].actor = 0;
    _actors[1].actor = 0;
}

LocationPopper::~LocationPopper()
{
    clear();
}

void LocationPopper::set(CardActor* firstActor, CardActor* secondActor)
{
    clear();

    if (firstActor)
    {
        _actors[0].actor = firstActor;
        _actors[0].oldPosition = firstActor->position();
        firstActor->position(_actors[0].oldPosition
            + QVector3D(-2.0f, 2.0f, 2.0f));
    }

    if (secondActor && secondActor != firstActor)
    {
        _actors[1].actor = secondActor;
        _actors[1].oldPosition = secondActor->position();
        secondActor->position(_actors[1].oldPosition
            + QVector3D(2.0f, 2.0f, 2.0f));
    }
}

void LocationPopper::clear()
{
    for (int i = 0; i < 2; ++i)
    {
        if (_actors[i].actor)
        {
            _actors[i].actor->position(_actors[i].oldPosition);
            _actors[i].actor = 0;
        }
    }
}
