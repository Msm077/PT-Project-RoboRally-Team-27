#include "AddRotatingGearAction.h"

AddRotatingGearAction::AddRotatingGearAction(ApplicationManager * pApp):Action(pApp)
{
}

void AddRotatingGearAction::ReadActionParameters()
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
    //AA
	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read the gearPos
	pOut->PrintMessage("New Rotating Gear: Click on its Cell ...");
	gearPos = pIn->GetCellClicked();
    // 3- Read whether the direction will be clockwise or not
    pOut->PrintMessage("Rotating Gear: Choose direction - Write CW for Clockwise, CCW for Anti-Clockwise ...");
	string msg = pIn->GetSrting(pOut);
	
	while (msg != "CW") {
		if (msg == "CW" || msg == "Cw" || msg == "cw")
		{
			clockwise = true;   // Clockwise
			pOut->PrintMessage("Rotating Gear: Clockwise direction selected.");
			break;
		}
		else if (msg == "CCW" || msg == "Ccw" || msg == "ccw")
		{
			clockwise = false;  // Anti-clockwise
			pOut->PrintMessage("Rotating Gear: Anti-Clockwise direction selected.");
			break;
		}
		else {
			pOut->PrintMessage("Error. Wrong Direction, Write CW for Clockwise, CCW for Anti-Clockwise ...");
			msg = pIn->GetSrting(pOut);
		}
	}
	

	// 4- Make the needed validations on the read parameters
	if (!gearPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Error: Invalid cell position! Click to continue...");
		gearPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (gearPos.GetCellNum() == 1)
	{
		pGrid->PrintErrorMessage("Error: Cannot place rotating gear in start cell (Cell 1)! Click to continue...");
		gearPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (pGrid->GetGameObjectFromCell(gearPos) != nullptr)
	{
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
		gearPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddRotatingGearAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1-Create a rotating gear object
	RotatingGear* pGear = new RotatingGear(gearPos, clockwise);

	// 2-get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 3-Add the rotating object to the GameObject of its Cell
	bool added = pGrid->AddObjectToCell(pGear);

	// 4-Check if the rotating gear was added and print an error message if gear couldn't be added
	if (!added)
	{
		delete pGear;
		pGrid->PrintErrorMessage("Error: Failed to add Rotating Gear! Click to continue...");
	}
	else
	{
		string msg = "Rotating gear (";
		msg += clockwise ? "Clockwise" : "Counter-Clockwise";
		msg += ") added successfully at cell " + to_string(gearPos.GetCellNum()) + ". Click to continue...";
		pOut->PrintMessage(msg);
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}
}

AddRotatingGearAction::~AddRotatingGearAction()
{
}
