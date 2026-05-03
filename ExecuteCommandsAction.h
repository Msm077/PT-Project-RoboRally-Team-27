#pragma once
#include "Action.h"
class ExecuteCommandsAction :
    public Action
{
public:
	ExecuteCommandsAction(ApplicationManager* pApp);

	// Reads parameters (Empty for this action, as no input is needed before executing)
	virtual void ReadActionParameters();

	// Executes the saved commands for the current player
	virtual void Execute();

	virtual ~ExecuteCommandsAction();
};

