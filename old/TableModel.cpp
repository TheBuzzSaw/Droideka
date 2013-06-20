#include "TableModel.hpp"

TableModel::TableModel(GLuint inTexture) : mTexture(inTexture)
{
    GLfloat vertices[] = {
        500.0f, 500.0f,
        500.0f, -500.0f,
        -500.0f, -500.0f,
        -500.0f, 500.0f,
        };

    mVertexBuffer.loadData(vertices, 4, 2);

    GLfloat textureCoordinates[] = {
        100.0f, 100.0f,
        100.0f, -100.0f,
        -100.0f, -100.0f,
        -100.0f, 100.0f,
        };

    mTextureBuffer.loadData(textureCoordinates, 4, 2);
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
