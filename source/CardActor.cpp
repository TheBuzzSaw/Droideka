#include "CardActor.hpp"

CardActor::CardActor() : _topTexture(0), _bottomTexture(0), _isTopVisible(true)
{
}

CardActor::~CardActor()
{
}

void CardActor::update(const QMatrix4x4& modelViewMatrix)
{
    _localMatrix.setToIdentity();
    _localMatrix.translate(_position);
    _localMatrix.rotate(_rotation.toDegrees(), 0.0f, 0.0f, 1.0f);
    _localMatrix.rotate(_flip.toDegrees(), 0.0f, 1.0f, 0.0f);

    _modelViewMatrix = modelViewMatrix * _localMatrix;

    QVector4D origin(0.0f, 0.0f, 0.0f, 1.0f);
    QVector4D modelViewOrigin = _modelViewMatrix * origin;

    QVector4D arrow(0.0f, 0.0f, 1.0f, 1.0f);
    QVector4D modelViewArrow = _modelViewMatrix * arrow;

    QVector3D direction = QVector3D(modelViewArrow - modelViewOrigin);
    QVector3D cameraToPolygon = QVector3D(modelViewOrigin).normalized();
    float dotProduct = QVector3D::dotProduct(cameraToPolygon, direction);
    _isTopVisible = dotProduct < 0.0f;
}
