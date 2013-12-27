#include "CardDrawTool.hpp"

CardDrawTool::CardDrawTool(BasicProgram& program, CardBuffer& buffer,
    QMatrix4x4& projectionMatrix)
    : _program(program),
    _buffer(buffer),
    _projectionMatrix(projectionMatrix)
{
}

CardDrawTool::~CardDrawTool()
{
}

void CardDrawTool::bind()
{
    _buffer.bind(_program.positionAttribute(), _program.textureAttribute());
}

void CardDrawTool::draw(CardActor& actor)
{
    _program.setMatrix(_projectionMatrix * actor.modelViewMatrix());
    _program.setHighlight(actor.highlight());
    _program.enableTexture(false);
    _buffer.drawMiddle();
    _program.enableTexture(true);

    if (actor.isTopVisible())
    {
        glBindTexture(GL_TEXTURE_2D, actor.topTexture());
        _buffer.drawTop();
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, actor.bottomTexture());
        _buffer.drawBottom();
    }
}
