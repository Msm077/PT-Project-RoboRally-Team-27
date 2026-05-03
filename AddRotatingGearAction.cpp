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
    pOut->PrintMessage("Rotating Gear: Choose direction - Click YES (left) for Clockwise, NO (right) for Anti-Clockwise ...");
	int x, y;
	pIn->GetPointClicked(x, y);

	
	if (x < UI.width / 2)
	{
		clockwise = true;   // Clockwise
		pOut->PrintMessage("Rotating Gear: Clockwise direction selected.");
	}
	else
	{
		clockwise = false;  // Anti-clockwise
		pOut->PrintMessage("Rotating Gear: Anti-Clockwise direction selected.");
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

	// 3-Add the rotating object to the GameObject of its Cell
	bool added = pGrid->AddObjectToCell(pGear);

	// 4-Check if the rotating gear was added and print an error message if gear couldn't be added
	if (!added)
	{
		pGrid->PrintErrorMessage("Error: Failed to add Rotating Gear! Click to continue...");
	}
}

AddRotatingGearAction::~AddRotatingGearAction()
{
}
