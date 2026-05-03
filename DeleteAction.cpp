#include "DeleteAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "GameObject.h"

DeleteAction::DeleteAction(ApplicationManager* pApp) : Action(pApp) {}

void DeleteAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Delete: Click on the cell you want to delete");
    targetPos = pIn->GetCellClicked();
    pOut->ClearStatusBar();
}

void DeleteAction::Execute()
{
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();

    if (!targetPos.IsValidCell())
    {
        pGrid->PrintErrorMessage("Error: Invalid cell");
        return;
    }

    GameObject* pObj = pGrid->GetGameObjectFromCell(targetPos);

    if (pObj == NULL)
    {
        pGrid->PrintErrorMessage("Error: No object in this cell");
        return;
    }

    // remove from cell then delete from memory forever
    pGrid->RemoveObjectFromCell(targetPos);
    pObj = NULL;

    pManager->UpdateInterface();
}

DeleteAction::~DeleteAction() {}