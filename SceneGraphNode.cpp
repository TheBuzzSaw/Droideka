#include "SceneGraphNode.hpp"
#include <QDebug>

SceneGraphNode::SceneGraphNode() : mParent(NULL)
{
}

SceneGraphNode::~SceneGraphNode()
{
    removeFromParentNode();
    removeAllChildrenNodes();
}

void SceneGraphNode::addChildNode(SceneGraphNode& inNode)
{
    inNode.removeFromParentNode();
    inNode.mParent = this;
    mChildren.push_back(&inNode);
}

void SceneGraphNode::removeChildNode(SceneGraphNode& inNode)
{
    if (inNode.mParent == this)
    {
        inNode.mParent = NULL;
        mChildren.remove(&inNode);
    }
}

void SceneGraphNode::removeAllChildrenNodes()
{
    for (std::list<SceneGraphNode*>::iterator i = mChildren.begin();
         i != mChildren.end(); ++i)
    {
        SceneGraphNode& node = *(*i);
        node.mParent = NULL;
    }

    mChildren.clear();
}

void SceneGraphNode::removeFromParentNode()
{
    if (mParent) mParent->removeChildNode(*this);
}

void SceneGraphNode::updateMatrices(const mat4f& inModelMatrix,
    const mat4f& inModelViewMatrix)
{
    willUpdate();
    mModelMatrix.multiply(inModelMatrix, mLocalMatrix);
    mModelViewMatrix.multiply(inModelViewMatrix, mLocalMatrix);
    didUpdate();

    for (std::list<SceneGraphNode*>::iterator i = mChildren.begin();
         i != mChildren.end(); ++i)
    {
        SceneGraphNode& node = *(*i);
        node.updateMatrices(mModelMatrix, mModelViewMatrix);
    }
}

void SceneGraphNode::willUpdate()
{
}

void SceneGraphNode::didUpdate()
{
}
