#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Belt.h"
#include "Antenna.h"
class AddAntennaAction :public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	CellPosition antPos; // The position 
	

	// Note: These parameters should be read in ReadActionParameters()
public:
	AddAntennaAction(ApplicationManager* pApp);
	virtual void ReadActionParameters(); // Reads AddAntennaAction action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new belt Object 
	// then Sets this belt object to the GameObject Pointer of its Cell


	virtual ~AddAntennaAction();
};

