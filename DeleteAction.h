#pragma once
#include "Action.h"
#include "CellPosition.h"

class DeleteAction : public Action
{
    CellPosition targetPos;

public:
    DeleteAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual ~DeleteAction();
};