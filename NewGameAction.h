#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
class NewGameAction :public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
public:

	NewGameAction(ApplicationManager* pApp);
	virtual void ReadActionParameters(); // Reads action parameters 

	virtual void Execute(); // Creates a new flag Object 
	// then Sets this flag object to the GameObject Pointer of its Cell

	~NewGameAction();
};

