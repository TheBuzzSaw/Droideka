#include "BasicBuilder.hpp"

BasicBuilder::BasicBuilder()
{
}

BasicBuilder::BasicBuilder(BasicBuilder&& other)
    : _values(std::move(other._values))
{
}

BasicBuilder::~BasicBuilder()
{
}

BasicBuilder& BasicBuilder::operator=(BasicBuilder&& other)
{
    if (this != &other)
    {
        _values = std::move(other._values);
    }

    return *this;
}

int BasicBuilder::vertexCount() const
{
    return _values.size() / 5;
}

void BasicBuilder::reserve(int vertexCount)
{
    _values.reserve(vertexCount * 5);
}

void BasicBuilder::add(QVector3D position, QVector2D textureCoordinate)
{
    _values.append(position.x());
    _values.append(position.y());
    _values.append(position.z());

    _values.append(textureCoordinate.x());
    _values.append(textureCoordinate.y());
}

void BasicBuilder::bufferData(QOpenGLFunctions& functions, GLenum usage) const
{
    functions.glBufferData(GL_ARRAY_BUFFER,
        _values.size() * sizeof(GLfloat),
        _values.constData(),
        usage);
}
