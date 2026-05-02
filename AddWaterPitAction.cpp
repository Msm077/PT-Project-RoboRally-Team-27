#include "AddWaterPitAction.h"

AddWaterPitAction::AddWaterPitAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddWaterPitAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Belt: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Belt: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();



	///TODO: Make the needed validations on the read parameters
	if (!waterPitPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Error: Invalid cell position! Click to continue...");
		waterPitPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (waterPitPos.GetCellNum() == 1)
	{
		pGrid->PrintErrorMessage("Error: Cannot place water pit in start cell (Cell 1)! Click to continue...");
		waterPitPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (pGrid->GetGameObjectFromCell(waterPitPos) != nullptr)
	{
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
		waterPitPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}


	// Clear messages
	pOut->ClearStatusBar();
}

void AddWaterPitAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a belt object with the parameters read from the user
	

}

AddWaterPitAction::~AddWaterPitAction()
{
}
