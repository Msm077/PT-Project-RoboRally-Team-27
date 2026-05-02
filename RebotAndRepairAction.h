#pragma once
#include "Action.h"
#include"input.h"


class RebotAndRepairAction : public Action
{
public:

	RebotAndRepairAction(ApplicationManager* pApp) : Action(pApp) {}
	virtual void ReadActionParameters() {}
	virtual void Execute();
};