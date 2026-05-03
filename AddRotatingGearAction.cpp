#include "AddRotatingGearAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "RotatingGear.h"

AddRotatingGearAction::AddRotatingGearAction(ApplicationManager * pApp):Action(pApp)
{
	clockwise = true; // safe default; will be overwritten in ReadActionParameters
}

void AddRotatingGearAction::ReadActionParameters()
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces

	// 2- Read the gearPos
	// 3- Read whether the direction will be clockwise or not

	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
    // 1. Get pointers to Input / Output
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // 2. Ask the user to click the cell for the gear
    pOut->PrintMessage("Click on the cell to add a rotating gear.");
    gearPos = pIn->GetCellClicked();

    // 4a. Validate: must be a valid cell
    if (!gearPos.IsValidCell())
    {
        pOut->PrintMessage("Invalid cell! Click to continue...");
        int x, y;
        pIn->GetPointClicked(x, y);
        pOut->ClearStatusBar();
        gearPos = CellPosition(-1, -1); // mark as invalid so Execute() aborts
        return;
    }

    // 4b. Validate: cannot place in cell 1 (bottom-left) or cell 55 (top-right)
    int cellNum = gearPos.GetCellNum();
    if (cellNum == 1 || cellNum == 55)
    {
        pOut->PrintMessage("Cannot place a rotating gear in the first or last cell! Click to continue...");
        int x, y;
        pIn->GetPointClicked(x, y);
        pOut->ClearStatusBar();
        gearPos = CellPosition(-1, -1);
        return;
    }

    // 3. Ask the user to choose the rotation direction
    //    Convention: left-click (x < half-width) = Clockwise,
    //                right-click (x >= half-width) = Counter-clockwise
    pOut->PrintMessage("Select rotation: Click LEFT half of window = Clockwise | RIGHT half = Counter-Clockwise");
    int x, y;
    pIn->GetPointClicked(x, y);
    clockwise = (x < UI.width / 2);

    // 5. Clear status bar
    pOut->ClearStatusBar();
}

void AddRotatingGearAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1-Create a rotating gear object
	// 2-get a pointer to the Grid from the ApplicationManager
	// 3-Add the rotating object to the GameObject of its Cell:
	// 4-Check if the rotating gear was added and print an errror message if flag couldn't be added
    // The first thing any Execute() does is read its parameters
    ReadActionParameters();

    // If ReadActionParameters() marked the position invalid, abort silently
    if (!gearPos.IsValidCell())
        return;

    // 1. Create the RotatingGear object
    RotatingGear* pGear = new RotatingGear(gearPos, clockwise);

    // 2. Get a pointer to the Grid
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // 3. Add the gear to its cell via Grid (Grid is the only class that touches CellList)
    bool added = pGrid->AddObjectToCell(pGear);

    // 4. Check result and report to the user
    if (!added)
    {
        // Cell already has a game object — discard the gear we just created
        delete pGear;
        pGrid->PrintErrorMessage("Cell already contains a game object! Rotating gear was NOT added. Click to continue...");
    }
    else
    {
        string msg = "Rotating gear (";
        msg += clockwise ? "Clockwise" : "Counter-Clockwise";
        msg += ") added successfully at cell " + to_string(gearPos.GetCellNum()) + ". Click to continue...";
        pOut->PrintMessage(msg);
        int x, y;
        pIn->GetPointClicked(x, y);
        pOut->ClearStatusBar();
    }
}

AddRotatingGearAction::~AddRotatingGearAction()
{
}
