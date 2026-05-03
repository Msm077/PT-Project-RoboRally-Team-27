#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Belt.h"
#include "WaterPit.h"
class AddWaterPitAction :public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	CellPosition waterPitPos; // 
	

	// Note: These parameters should be read in ReadActionParameters()
public:
	AddWaterPitAction(ApplicationManager* pApp);
	virtual void ReadActionParameters(); // Reads AddWaterPitAction action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new belt Object 
	// then Sets this belt object to the GameObject Pointer of its Cell


	virtual ~AddWaterPitAction();
};

