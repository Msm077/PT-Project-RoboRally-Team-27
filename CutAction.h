#pragma once
#include "Action.h"
#include "CellPosition.h"

class CutAction : public Action
{
    CellPosition srcPos;

public:
    CutAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual ~CutAction();
};