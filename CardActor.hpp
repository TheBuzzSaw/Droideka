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

    inline void position(float inX, float inY)
    {
        mPosition[0] = inX;
        mPosition[1] = inY;
    }

    inline void setHighlight(float* inHighlight) { mHighlight = inHighlight; }
    inline float z() const { return mPosition[2]; }
    inline const vec3f& position() const { return mPosition; }

    bool contains(float inX, float inY);
    void rotate90();
    void flip180();
    void setThickness(float inThickness);

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
    float mOffsetBase;
    float mThickness;
    float mRotation;
    float mFlip;
    bool mIsHorizontal;
    int mRotationStepsLeft;
    int mFlipStepsLeft;
};

#endif
