#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Flag.h"
#include "Workshop.h"
#include "Belt.h"
#include "WaterPit.h"
#include "DangerZone.h"
#include "RotatingGear.h"
#include "Antenna.h"
class ReadGridAction :public Action
{
	// Always add action parameters as private data members

	// [Action Parameters]
	ifstream inFile;
	string saveName;
public:
	
	ReadGridAction(ApplicationManager *pApp);
	virtual void ReadActionParameters(); // Reads action parameters 

	virtual void Execute(); // Creates a new flag Object 
							// then Sets this flag object to the GameObject Pointer of its Cell

	~ReadGridAction();
};

