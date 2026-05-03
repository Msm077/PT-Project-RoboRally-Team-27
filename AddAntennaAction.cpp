#include "AddAntennaAction.h"

AddAntennaAction::AddAntennaAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddAntennaAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Antenna: Click on its Cell ...");
	antPos = pIn->GetCellClicked();

	



	///TODO: Make the needed validations on the read parameters
    if (!antPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Error: Invalid cell position! Click to continue...");
		antPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (antPos.GetCellNum() == 1)
	{
		pGrid->PrintErrorMessage("Error: Cannot place workshop in start cell (Cell 1)! Click to continue...");
		antPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (pGrid->GetGameObjectFromCell(antPos) != nullptr)
	{
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
		antPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}


	// Clear messages
	pOut->ClearStatusBar();
}

void AddAntennaAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

Antenna* pAntenna = new Antenna(antPos);

	Grid* pGrid = pManager->GetGrid();

	bool added = pGrid->AddObjectToCell(pAntenna);

	if (!added)
	{
		pGrid->PrintErrorMessage("Error: Failed to add Antenna! Click to continue...");
	}	

}

AddAntennaAction::~AddAntennaAction()
{
}
