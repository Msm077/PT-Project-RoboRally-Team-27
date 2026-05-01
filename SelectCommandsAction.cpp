#include "SelectCommandsAction.h"
#include "Player.h"
#include "Input.h"
#include<iostream>
#include"Grid.h"
#include "GameState.h"
using namespace std;

SelectCommandsAction::SelectCommandsAction(ApplicationManager* pApp) : Action(pApp)
{
	// every action needs to access the game's tools to work. 
	//cuz i passed pApp to the parent Action class, 
	// i can now use pManager inside other functions to reach everything else in the game
    numSelected = 0; // Initializing our counter
}


// mapping fn used in "ReadActionParameters" fn to make the message for the user clearer

string GetCommandName(Command cmd)
{
	switch (cmd)
	{
	case MOVE_FORWARD_ONE_STEP:     return "Move Forward 1 Step";
	case MOVE_BACKWARD_ONE_STEP:    return "Move Backward 1 Step";
	case MOVE_FORWARD_TWO_STEPS:    return "Move Forward 2 Steps";
	case MOVE_BACKWARD_TWO_STEPS:   return "Move Backward 2 Steps";
	case MOVE_FORWARD_THREE_STEPS:  return "Move Forward 3 Steps";
	case MOVE_BACKWARD_THREE_STEPS: return "Move Backward 3 Steps";
	case ROTATE_CLOCKWISE:          return "Rotate Clockwise";
	case ROTATE_COUNTERCLOCKWISE:   return "Rotate Counter-Clockwise";
	default:                        return "No Command";
	}
}

void SelectCommandsAction::ReadActionParameters()
{
	// 1st part
	// Retrieve the Grid from ApplicationManager to access the board and game data.
	// Get Input and Output pointers to handle all user interaction and drawing through the graphics library.
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	GameState* pGS = pManager->GetGameState();

	// 2nd part determine the current player & his health  to update his data
	Player* pCurrentPlayer = pManager->GetGameState()->GetCurrentPlayer();
	int health = pManager->GetGameState()->GetCurrentPlayer()->GetHealth();

	// Generate the random pool from which the use can choose items
	pGS->GenerateRandomCommands();
	Command* pool = pGS->GetRandomCommandsPool();
	int poolSize = MaxAvailableCommands;

	// 3rd part get min(5, health)
	int min = 5;
	if (health < 5) {
		min = health;
	}
	// 4th part putting the user in the situation
	pOut->PrintMessage(" choose " + to_string(min) + " commands ");

	// 5th part clear the player's former commands
	pCurrentPlayer->ClearSavedCommands();

	// 6th part: loop to get the selected commands using the input:: GetSelectedCommandIndex()
	for (int i = 0; i < min; i++) {

		// Update UI by showing the pool and the slots being filled
		pOut->CreateCommandsBar(pCurrentPlayer->GetSavedCommands(), i, pool, poolSize);

		int poolIndex = -1;

		// wait until a valid index within the 10-slot pool is clicked and to overcome any unexpected inpputs
		while (poolIndex < 0 || poolIndex >= poolSize)
		{
			// Input::GetSelectedCommandIndex() returns the 0-9 index of the clicked icon in the pool
			poolIndex = pIn->GetSelectedCommandIndex();

			if (poolIndex == -1) {
				pOut->PrintMessage("invalid input! Please select a command from the AVAILABLE pool.");
			}
		}
		// mapping according to the enum command
		Command selectedCmd = pool[poolIndex];

		// updating the player object with t he selected commands
		pCurrentPlayer->AddSavedCommand(selectedCmd);

		string cmdName = GetCommandName(selectedCmd);
		pOut->PrintMessage("Slot " + to_string(i + 1) + ": " + cmdName + " saved.");
	}
	// show the complete set of selected commands
	pOut->CreateCommandsBar(pCurrentPlayer->GetSavedCommands(), min, pool, poolSize);
	
}

void SelectCommandsAction::Execute()
{


	// 1. Get the commands
	ReadActionParameters();

	// notify the user
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pGrid->GetOutput()->PrintMessage("Commands saved! Ready to move.");
}

SelectCommandsAction::~SelectCommandsAction()
{
}
