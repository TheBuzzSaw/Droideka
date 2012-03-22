#ifndef CARDNODE_HPP
#define CARDNODE_HPP

#include "Actor.hpp"
#include "Vectors.hpp"
#include "CardModel.hpp"

class CardActor : public Actor
{
public:
    CardActor(CardModel& inCardModel, GLuint inFrontTexture,
        GLuint inBackTexture);
    virtual ~CardActor();

    virtual void draw();

    inline mat4f& matrix() { return localMatrix(); }

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
    float mRotation;
    float mFlip;
};

#endif
