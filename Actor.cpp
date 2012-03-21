#include "Actor.hpp"
#include <QGLWidget>

Actor::Actor() : mNextActor(0), mPreviousActor(0)
{
}

Actor::~Actor()
{
    removeFromChain();
}

void Actor::draw()
{
}

void Actor::addToChain(Actor& inActor)
{
    mPreviousActor = &inActor;
    mNextActor = inActor.mNextActor;
    inActor.mNextActor = this;
    if (mNextActor) mNextActor->mPreviousActor = this;
}

void Actor::removeFromChain()
{
    if (mPreviousActor) mPreviousActor->mNextActor = mNextActor;
    if (mNextActor) mNextActor->mPreviousActor = mPreviousActor;

    mNextActor = 0;
    mPreviousActor = 0;
}

void Actor::drawChain()
{
    for (Actor* a = mNextActor; a; a = a->mNextActor)
    {
        glLoadMatrixf(a->modelViewMatrix());
        a->draw();
    }
}
