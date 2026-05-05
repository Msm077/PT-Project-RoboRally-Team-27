#include "CopyAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "GameObject.h"
#include "Antenna.h"
#include "Flag.h"
CopyAction::CopyAction(ApplicationManager* pApp) : Action(pApp) {}

void CopyAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Click on the cell you want to copy");
    srcPos = pIn->GetCellClicked();
    pOut->ClearStatusBar();
}

void CopyAction::Execute()
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
    if (dynamic_cast<Flag*>(pObj) != nullptr) {
        pGrid->PrintErrorMessage("Error: Cannot Copy Flags");
        return;
    }
    if (dynamic_cast<Antenna*>(pObj) != nullptr) {
        pGrid->PrintErrorMessage("Error: Cannot Copy Antenna");
        return;
    }

    // just save the pointer in clipboard, object stays in its cell
    pGrid->SetClipboard(pObj);

    pGrid->GetOutput()->PrintMessage("Copied! Use Paste to place it. Click to Paste");
    int x, y;
    pGrid->GetInput()->GetPointClicked(x, y);
    pGrid->GetOutput()->ClearStatusBar();
}

CopyAction::~CopyAction() {}