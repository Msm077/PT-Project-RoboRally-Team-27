#include "AddWorkshopAction.h"

AddWorkshopAction::AddWorkshopAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddWorkshopAction::ReadActionParameters()
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
    if (!workshopPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Error: Invalid cell position! Click to continue...");
		workshopPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (workshopPos.GetCellNum() == 1)
	{
		pGrid->PrintErrorMessage("Error: Cannot place workshop in start cell (Cell 1)! Click to continue...");
		workshopPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (pGrid->GetGameObjectFromCell(workshopPos) != nullptr)
	{
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
		workshopPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}


	// Clear messages
	pOut->ClearStatusBar();
}

void AddWorkshopAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

Workshop* pWorkshop = new Workshop(workshopPos);

	Grid* pGrid = pManager->GetGrid();

	bool added = pGrid->AddObjectToCell(pWorkshop);

	if (!added)
	{
		pGrid->PrintErrorMessage("Error: Failed to add Workshop! Click to continue...");
	}	

}

AddWorkshopAction::~AddWorkshopAction()
{
}
