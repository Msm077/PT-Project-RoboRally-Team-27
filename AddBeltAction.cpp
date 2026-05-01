#include "AddBeltAction.h"

AddBeltAction::AddBeltAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddBeltAction::ReadActionParameters()
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
	//AA
	if (!startPos.IsValidCell() || !endPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Error: Invalid cell position! Click to continue...");
		startPos = CellPosition();
		endPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (startPos.GetCellNum() == 1)
	{
		pGrid->PrintErrorMessage("Error: Belt start cell cannot be the start cell (Cell 1)! Click to continue...");
		startPos = CellPosition();
		endPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (startPos.GetCellNum() == endPos.GetCellNum())
	{
		pGrid->PrintErrorMessage("Error: Belt start and end cells cannot be the same! Click to continue...");
		startPos = CellPosition();
		endPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	
	if (startPos.HCell() != endPos.HCell() && startPos.VCell() != endPos.VCell())
	{
		pGrid->PrintErrorMessage("Error: Belt must be horizontal or vertical (not diagonal)! Click to continue...");
		startPos = CellPosition();
		endPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}


	if (pGrid->GetGameObjectFromCell(startPos) != nullptr)
	{
		pGrid->PrintErrorMessage("Error: Start cell already has an object! Click to continue...");
		startPos = CellPosition();
		endPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	
	GameObject* pEndObject = pGrid->GetGameObjectFromCell(endPos);
	if (pEndObject != nullptr && dynamic_cast<Flag*>(pEndObject) != nullptr)
	{
		pGrid->PrintErrorMessage("Error: End cell cannot contain a flag! Click to continue...");
		startPos = CellPosition();
		endPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}
	

	
	if (pGrid->IsStartCellOfBelt(endPos))
	{
		pGrid->PrintErrorMessage("Error: End cell cannot be the start cell of another belt! Click to continue...");
		startPos = CellPosition();
		endPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}
	



	// Clear messages
	pOut->ClearStatusBar();
}

void AddBeltAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a belt object with the parameters read from the user
	Belt * pBelt = new Belt(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

										
	bool added = pGrid->AddObjectToCell(pBelt);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the belt is created and added to the GameObject of its Cell, so we finished executing the AddBeltAction

}

AddBeltAction::~AddBeltAction()
{
}
