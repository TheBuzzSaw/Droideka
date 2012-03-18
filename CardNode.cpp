#include "CardNode.hpp"

CardNode::CardNode()
{
}

CardNode::~CardNode()
{
}

void CardNode::willUpdate()
{
    localMatrix().loadIdentity();
    localMatrix().rotateZ(0.0f);
}

void CardNode::didUpdate()
{
    vec4f origin;
    origin[3] = 1.0f;

    modelMatrix().transform(origin, mModelOrigin);
    modelViewMatrix().transform(origin, mModelViewOrigin);

    origin[2] = 1.0f;
    modelViewMatrix().transform(origin, mDirection);

    mDirection[0] -= mModelViewOrigin[0];
    mDirection[1] -= mModelViewOrigin[1];
    mDirection[2] -= mModelViewOrigin[2];

    mRenderFront = mDirection[2] > 0.0f;
}
