#include "TableModel.hpp"

TableModel::TableModel(GLuint inTexture) : mTexture(inTexture)
{
}

TableModel::~TableModel()
{
}

void TableModel::draw()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    mVertexBuffer.vertexPointer();
    mTextureBuffer.textureCoordinatePointer();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    mTextureBuffer.disableClientState();
    mVertexBuffer.disableClientState();
    glDisable(GL_TEXTURE_2D);
}
