#pragma once
#include "Action.h"
#include "CellPosition.h"

class CopyAction : public Action
{
    CellPosition srcPos;

public:
    CopyAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual ~CopyAction();
};