#ifndef CARDDRAWTOOL_HPP
#define CARDDRAWTOOL_HPP

#include "MainProgram.hpp"
#include "CardBuffer.hpp"
#include "CardActor.hpp"
#include <QMatrix4x4>

class CardDrawTool
{
public:
    CardDrawTool(MainProgram& program, CardBuffer& buffer,
        QMatrix4x4& projectionMatrix);
    ~CardDrawTool();

    void bind();
    void draw(CardActor& actor);

private:
    CardDrawTool(const CardDrawTool& other);
    CardDrawTool& operator=(const CardDrawTool& other);

    MainProgram& _program;
    CardBuffer& _buffer;
    QMatrix4x4& _projectionMatrix;
};

#endif
