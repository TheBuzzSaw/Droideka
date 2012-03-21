#ifndef CARDNODE_HPP
#define CARDNODE_HPP

#include "SceneGraphNode.hpp"
#include "Vectors.hpp"
#include "CardModel.hpp"

class CardNode : public SceneGraphNode
{
public:
    CardNode(CardModel& inCardModel, GLuint inFrontTexture,
        GLuint inBackTexture);
    virtual ~CardNode();

    void draw();

protected:
    virtual void willUpdate();
    virtual void didUpdate();

private:
    CardModel& mCardModel;
    GLuint mFrontTexture;
    GLuint mBackTexture;

    vec4f mModelOrigin;
    vec4f mModelViewOrigin;
    vec4f mDirection;
    bool mDrawFront;

    vec3f mPosition;
};

#endif
