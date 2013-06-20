#include "TableActor.hpp"

TableActor::TableActor(TableModel& inModel) : mTableModel(inModel)
{
}

TableActor::~TableActor()
{
}

void TableActor::draw()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    mTableModel.draw();
}
