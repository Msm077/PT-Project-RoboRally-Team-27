#include "AddDangerZoneAction.h"

AddDangerZoneAction::AddDangerZoneAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddDangerZoneAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the Pos parameter
	pOut->PrintMessage("New Danger Zone: Click on its Cell ...");
	dangerZonePos = pIn->GetCellClicked();



	///TODO: Make the needed validations on the read parameters
    //AA
	if (!dangerZonePos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Error: Invalid cell position! Click to continue...");
		dangerZonePos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}
	
	if (dangerZonePos.GetCellNum() == 1)
	{
		pGrid->PrintErrorMessage("Error: Cannot place danger zone in start cell (Cell 1)! Click to continue...");
		dangerZonePos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	
	if (pGrid->GetGameObjectFromCell(dangerZonePos) != nullptr)
	{
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
		dangerZonePos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}


	// Clear messages
	pOut->ClearStatusBar();
}

void AddDangerZoneAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

DangerZone* pDangerZone = new DangerZone(dangerZonePos);

	Grid* pGrid = pManager->GetGrid();

	bool added = pGrid->AddObjectToCell(pDangerZone);

	if (!added)
	{
		pGrid->PrintErrorMessage("Error: Failed to add Danger Zone! Click to continue...");
	}
	

}

AddDangerZoneAction::~AddDangerZoneAction()
{
}
