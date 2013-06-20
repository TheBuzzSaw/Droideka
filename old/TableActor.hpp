#ifndef TABLEACTOR_HPP
#define TABLEACTOR_HPP

#include "Actor.hpp"
#include "TableModel.hpp"

class TableActor : public Actor
{
public:
    TableActor(TableModel& inModel);
    virtual ~TableActor();

    virtual void draw();

private:
    TableModel& mTableModel;
};

#endif
