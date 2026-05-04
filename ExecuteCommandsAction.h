#pragma once
#include "Action.h"


class ExecuteCommandsAction : public Action
{
public:

	ExecuteCommandsAction(ApplicationManager* pApp);

	// Nothing to read -- execution needs no extra GUI input.
	virtual void ReadActionParameters() override;

	// Runs Move(), advances the turn, and triggers shooting if the round ended.
	virtual void Execute() override;

	virtual ~ExecuteCommandsAction();
};
