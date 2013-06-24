#ifndef CARD_HPP
#define CARD_HPP

#include <QOpenGLFunctions>

class Card
{
public:
    Card(GLuint frontTexture, GLuint backTexture);
    Card(const Card& other);
    ~Card();

    Card& operator=(const Card& other);

private:
    GLuint _frontTexture;
    GLuint _backTexture;
};

#endif
