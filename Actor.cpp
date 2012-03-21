#include "Actor.hpp"
#include <QGLWidget>

Actor::Actor() : mNextActor(NULL), mPreviousActor(NULL)
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

    mNextActor = NULL;
    mPreviousActor = NULL;
}

void Actor::drawChain()
{
    for (Actor* a = mNextActor; a; a = a->mNextActor)
    {
        glLoadMatrixf(a->modelViewMatrix());
        a->draw();
    }
}
