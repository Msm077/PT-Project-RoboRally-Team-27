#include "AddAntennaAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "Antenna.h"

AddAntennaAction::AddAntennaAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddAntennaAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Add Antenna: Click on the cell to place the antenna ...");
    antPos = pIn->GetCellClicked();

    if (!antPos.IsValidCell())
    {
        pGrid->PrintErrorMessage("Error: Invalid cell. Click to continue ...");
        antPos = CellPosition();
        return;
    }

    if (antPos.GetCellNum() == 1 || antPos.GetCellNum() == 55)
    {
        pGrid->PrintErrorMessage("Error: Cannot place antenna on cell 1 or 55. Click to continue ...");
        antPos = CellPosition();
        return;
    }

    if (pGrid->GetGameObjectFromCell(antPos) != NULL)
    {
        pGrid->PrintErrorMessage("Error: Cell already has an object. Click to continue ...");
        antPos = CellPosition();
        return;
    }
    if (pGrid->GetNumberofObject(Antennas) != 0)
    {
        pGrid->PrintErrorMessage("Error: Only one flag is allowed on the grid! Click to continue...");
        antPos = CellPosition();
        pOut->ClearStatusBar();
        return;
        pOut->ClearStatusBar();
    }
}

void AddAntennaAction::Execute()
{
    ReadActionParameters();

    // if antPos is invalid (set to -1,-1 by validation), stop
    if (!antPos.IsValidCell())
        return;

    Grid* pGrid = pManager->GetGrid();

    // Create the antenna object
    Antenna* pAntenna = new Antenna(antPos);

    // Add it to the grid
    bool added = pGrid->AddObjectToCell(pAntenna);

    if (!added)
    {
        delete pAntenna;
        pGrid->PrintErrorMessage("Error: Cell already has an object. Click to continue ...");
        return;
    }
}

AddAntennaAction::~AddAntennaAction()
{
}