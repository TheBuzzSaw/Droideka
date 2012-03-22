#include "TableActor.hpp"

TableActor::TableActor(TableModel& inModel) : mTableModel(inModel)
{
}

TableActor::~TableActor()
{
}

void TableActor::draw()
{
    mTableModel.draw();
}
