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
    void update();

    inline void setHighlight(float* inHighlight) { mHighlight = inHighlight; }

    inline float x() const { return mPosition[0]; }
    inline float y() const { return mPosition[1]; }
    inline float z() const { return mUnderneath + mPosition[2]; }

    inline float radiusZ() const { return mRadiusZ; }

    inline bool isHorizontal() const { return mRadiusX > mRadiusY; }
    inline bool isVertical() const { return mRadiusY > mRadiusX; }
    inline const vec3f& position() const { return mPosition; }

    inline CardActor* parent() const { return mParent; }
    inline CardActor* child() const { return mChild; }

    inline CardActor* lineage() const { return mLineage; }

    void confirmParent();
    void setChild(CardActor* inCardActor);

    bool contains(float inX, float inY);
    bool overlaps(const CardActor& inCardActor);
    void rotate90();
    void flip180();
    void setThickness(float inThickness);
    void setPosition(float inX, float inY);
    void move(float inDeltaX, float inDeltaY);

protected:
    virtual void willUpdate();
    virtual void didUpdate();

private:
    static bool isInRange(float inPointA, float inRadiusA, float inPointB,
        float inRadiusB);

    void updateUnderneath();
    void updateUnderneath(float inPreviousUnderneath);
    void setLineage(CardActor* inLineage);

    CardActor* mLineage;
    CardActor* mParent;
    CardActor* mChild;

    CardModel& mCardModel;
    GLuint mFrontTexture;
    GLuint mBackTexture;

    vec4f mModelOrigin;
    vec4f mModelViewOrigin;
    vec4f mDirection;
    bool mDrawFront;

    vec3f mHighlight;
    vec3f mPosition;
    float mUnderneath;
    float mRadiusX;
    float mRadiusY;
    float mRadiusZ;
    float mOccupyZ;
    float mThickness;
    float mRotation;
    float mFlip;
    int mRotationStepsLeft;
    int mFlipStepsLeft;
};

#endif
