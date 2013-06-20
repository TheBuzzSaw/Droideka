#ifndef PINGMODEL_HPP
#define PINGMODEL_HPP

#include "IndexBufferObject.hpp"
#include "Vectors.hpp"

class PingModel
{
public:
    PingModel();
    ~PingModel();

    void draw(float inRed, float inGreen, float inBlue);

private:
    VertexBufferObject mVertexBuffer;
};

#endif
