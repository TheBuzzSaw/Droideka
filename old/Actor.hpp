#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "SceneGraphNode.hpp"

class Actor : public SceneGraphNode
{
public:
    Actor();
    virtual ~Actor();

    virtual void draw();

    void addToChain(Actor& inActor);
    void removeFromChain();
    void drawChain();

private:
    Actor* mNextActor;
    Actor* mPreviousActor;
};

#endif
