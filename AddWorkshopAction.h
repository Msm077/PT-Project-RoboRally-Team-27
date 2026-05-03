#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Belt.h"
#include "Workshop.h"
class AddWorkshopAction :public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	CellPosition workshopPos; // The position 
	

	// Note: These parameters should be read in ReadActionParameters()
public:
	AddWorkshopAction(ApplicationManager* pApp);
	virtual void ReadActionParameters(); // Reads AddWorkshopAction action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new belt Object 
	// then Sets this belt object to the GameObject Pointer of its Cell


	virtual ~AddWorkshopAction();
};

