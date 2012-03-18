#ifndef CARDNODE_HPP
#define CARDNODE_HPP

#include "SceneGraphNode.hpp"
#include "Vectors.hpp"

class CardNode : public SceneGraphNode
{
public:
    CardNode();
    virtual ~CardNode();

protected:
    virtual void willUpdate();
    virtual void didUpdate();

private:
    vec4f mModelOrigin;
    vec4f mModelViewOrigin;
    vec4f mDirection;
    bool mRenderFront;
};

#endif
