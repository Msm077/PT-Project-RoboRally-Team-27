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



	// Clear messages
	pOut->ClearStatusBar();
}

void AddBeltAction::Execute()
{
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();

    // --- Validation 1: both positions must be valid ---
    if (!startPos.IsValidCell() || !endPos.IsValidCell())
    {
        pGrid->PrintErrorMessage("Error: Invalid cell selected. Click to continue ...");
        return;
    }

    // --- Validation 2: cannot place in cell 1 (bottom-left = vCell=4, hCell=0) ---
    if (startPos.GetCellNum() == 1 || endPos.GetCellNum() == 1)
    {
        pGrid->PrintErrorMessage("Error: Cannot place belt on cell 1. Click to continue ...");
        return;
    }

    // --- Validation 3: cannot place in cell 55 (top-right = vCell=0, hCell=10) ---
    if (startPos.GetCellNum() == 55 || endPos.GetCellNum() == 55)
    {
        pGrid->PrintErrorMessage("Error: Cannot place belt on cell 55. Click to continue ...");
        return;
    }

    // --- Validation 4: start and end must be in the same row OR same column ---
    if (startPos.VCell() != endPos.VCell() && startPos.HCell() != endPos.HCell())
    {
        pGrid->PrintErrorMessage("Error: Belt must be horizontal or vertical. Click to continue ...");
        return;
    }

    // --- Validation 5: start cell must not already have a game object ---
    // Grid's AddObjectToCell handles this (returns false if occupied)

    // --- Validation 6: end cell cannot contain a flag ---
    // We check via Cell's HasFlag() helper (sanctioned dynamic_cast in Cell)
    // Grid provides access through a helper — we ask Grid to validate
    if (pGrid->CellHasFlag(endPos))
    {
        pGrid->PrintErrorMessage("Error: Belt end cell cannot contain a flag. Click to continue ...");
        return;
    }

    // --- Validation 7: end cell cannot be the start of another belt ---
    if (pGrid->CellHasBelt(endPos))
    {
        pGrid->PrintErrorMessage("Error: Belt end cell cannot be the start of another belt. Click to continue ...");
        return;
    }

    // --- All validations passed: create and add the belt ---
    Belt* pBelt = new Belt(startPos, endPos);
    bool added = pGrid->AddObjectToCell(pBelt);

    if (!added)
    {
        delete pBelt; // prevent memory leak
        pGrid->PrintErrorMessage("Error: Start cell already has an object. Click to continue ...");
    }
}

AddBeltAction::~AddBeltAction()
{
}
