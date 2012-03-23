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

    inline void setHighlight(float* inHighlight) { mHighlight = inHighlight; }
    inline float z() const { return mPosition[2]; }
    inline const vec3f& position() const { return mPosition; }
    inline void position(float* inPosition) { mPosition = inPosition; }
    bool contains(float inX, float inY);
    void rotate90();

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

    vec3f mHighlight;
    vec3f mPosition;
    float mRotation;
    float mFlip;
    bool mIsHorizontal;
    int mRotationStepsLeft;
};

#endif
