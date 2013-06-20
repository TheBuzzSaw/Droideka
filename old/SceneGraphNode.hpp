#ifndef SCENEGRAPHNODE_HPP
#define SCENEGRAPHNODE_HPP

#include "Matrix4x4.hpp"
#include <list>

class SceneGraphNode
{
public:
    SceneGraphNode();
    virtual ~SceneGraphNode();

    inline const mat4f& modelViewMatrix() const
    {
        return mModelViewMatrix;
    }

    inline const mat4f& modelMatrix() const
    {
        return mModelMatrix;
    }

    void addChildNode(SceneGraphNode& inNode);
    void removeChildNode(SceneGraphNode& inNode);
    void removeAllChildrenNodes();
    void removeFromParentNode();

    void updateMatrices(const mat4f& inModelMatrix,
        const mat4f& inModelViewMatrix);

protected:
    inline mat4f& localMatrix() { return mLocalMatrix; }
    inline const mat4f& localMatrix() const { return mLocalMatrix; }

    virtual void willUpdate();
    virtual void didUpdate();

private:
    mat4f mLocalMatrix;
    mat4f mModelViewMatrix;
    mat4f mModelMatrix;

    SceneGraphNode* mParent;
    std::list<SceneGraphNode*> mChildren;
};

#endif
