#include "PingModel.hpp"
#include <QDebug>
#include <cmath>

PingModel::PingModel()
{
    const size_t VertexCount = 16;
    GLfloat vertices[VertexCount * 2];
    GLfloat* vertex = vertices;

    for (size_t i = 0; i < VertexCount; ++i)
    {
        float radians = 3.1415926535898f * 2.0f * float(i) / float(VertexCount);
        *vertex++ = sin(radians);
        *vertex++ = cos(radians);
    }

    mVertexBuffer.loadData(vertices, VertexCount, 2);
}

PingModel::~PingModel()
{
}

void PingModel::draw(float inRed, float inGreen, float inBlue)
{
    glColor3f(inRed, inGreen, inBlue);
    mVertexBuffer.draw(GL_LINE_LOOP);
}
