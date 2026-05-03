#include "PasteAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "GameObject.h"

PasteAction::PasteAction(ApplicationManager* pApp) : Action(pApp) {}

void PasteAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    pOut->PrintMessage("Paste: Click on the destination cell ...");
    destPos = pIn->GetCellClicked();
    pOut->ClearStatusBar();
}

void PasteAction::Execute()
{
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();

    // check clipboard has something
    GameObject* pClipboard = pGrid->GetClipboard();
    if (pClipboard == NULL)
    {
        pGrid->PrintErrorMessage("Error: Nothing in clipboard. Click to continue ...");
        return;
    }

    if (!destPos.IsValidCell())
    {
        pGrid->PrintErrorMessage("Error: Invalid destination cell. Click to continue ...");
        return;
    }

    // create a brand new independent object at the destination
    GameObject* pNewObject = pClipboard->Photocopy(destPos);

    // try to add it to the destination cell
    bool added = pGrid->AddObjectToCell(pNewObject);

    if (!added)
    {
        delete pNewObject;
        pGrid->PrintErrorMessage("Error: Cell already occupied! Click to continue ...");
        return;
    }

    // clipboard stays so user can paste multiple times
    pManager->UpdateInterface();
}

PasteAction::~PasteAction() {}