#include "CutAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "GameObject.h"

CutAction::CutAction(ApplicationManager* pApp) : Action(pApp) {}

void CutAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Cut: Click on the cell you want to cut from");
    srcPos = pIn->GetCellClicked();
    pOut->ClearStatusBar();
}

void CutAction::Execute()
{
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();

    if (!srcPos.IsValidCell())
    {
        pGrid->PrintErrorMessage("Error: Invalid cell");
        return;
    }

    GameObject* pObj = pGrid->GetGameObjectFromCell(srcPos);

    if (pObj == NULL)
    {
        pGrid->PrintErrorMessage("Error: No object in this cell");
        return;
    }

    // remove from cell WITHOUT deleting the object
    pGrid->RemoveObjectFromCell(srcPos);

    // store object in clipboard
    pGrid->SetClipboard(pObj);

    pManager->UpdateInterface();

    pGrid->GetOutput()->PrintMessage("Cut! Use Paste to place it");
    int x, y;
    pGrid->GetInput()->GetPointClicked(x, y);
    pGrid->GetOutput()->ClearStatusBar();
}

CutAction::~CutAction() {}