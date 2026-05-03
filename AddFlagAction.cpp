#include "AddFlagAction.h"



AddFlagAction::AddFlagAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void AddFlagAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Flag: Click on its Cell ...");
	flagPos = pIn->GetCellClicked();


	if (!flagPos.IsValidCell())
	{
		pGrid->PrintErrorMessage("Error: Invalid cell position! Click to continue...");
		flagPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (flagPos.GetCellNum() == 1)
	{
		pGrid->PrintErrorMessage("Error: Cannot place flag in start cell (Cell 1)! Click to continue...");
		flagPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	if (flagPos.GetCellNum() == 55)
	{
		pGrid->PrintErrorMessage("Error: Cannot place flag in cell 55! Click to continue...");
		flagPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	//if (pGrid->GetFlagPosition().IsValidCell())
	//{
	//	pGrid->PrintErrorMessage("Error: Only one flag is allowed on the grid! Click to continue...");
	//	flagPos = CellPosition();
	//	pOut->ClearStatusBar();
	//	return;
	//}

	if (pGrid->GetGameObjectFromCell(flagPos) != nullptr)
	{
		pGrid->PrintErrorMessage("Error: Cell already has an object! Click to continue...");
		flagPos = CellPosition();
		pOut->ClearStatusBar();
		return;
	}

	pOut->ClearStatusBar();
}

void AddFlagAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==
    //AA
	// 1-Create a flag object
	Flag* pFlag = new Flag(flagPos);

	// 2-get a pointer to the Grid from the ApplicationManager
	Grid* pGrid = pManager->GetGrid();

	// 3-Add the flag object to the GameObject of its Cell
	bool added = pGrid->AddObjectToCell(pFlag);

	// 4-Check if the flag was added and print an error message if flag couldn't be added
	if (!added)
	{
		pGrid->PrintErrorMessage("Error: Failed to add Flag! Click to continue...");
	}
}

AddFlagAction::~AddFlagAction()
{
}
