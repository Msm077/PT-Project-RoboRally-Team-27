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
	int min = pCurrentPlayer->GetMaxCommands(); // returns 6 if Extended Memory equipped
	if (health < min) min = health;

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
		while (poolIndex < 0 || poolIndex >= poolSize || pool[poolIndex] == NO_COMMAND)
		{
			// Input::GetSelectedCommandIndex() returns the 0-9 index of the clicked icon in the pool
			poolIndex = pIn->GetSelectedCommandIndex();

			if (poolIndex == -1) {
				pOut->PrintMessage("invalid input! Please select a command from the pool.");
			}
			else if (poolIndex >= 0 && poolIndex < poolSize && pool[poolIndex] == NO_COMMAND)
				pOut->PrintMessage("That command was already chosen! Pick a different one.");
		}
		// mapping according to the enum command
		Command selectedCmd = pool[poolIndex];

		// updating the player object with t he selected commands
		pCurrentPlayer->AddSavedCommand(selectedCmd);

		//marks slots as used
		pool[poolIndex] = NO_COMMAND;

		string cmdName = GetCommandName(selectedCmd);
		pOut->PrintMessage("Slot " + to_string(i + 1) + ": " + cmdName + " saved.");
	}
	// show the complete set of selected commands
	pOut->CreateCommandsBar(pCurrentPlayer->GetSavedCommands(), min, pool, poolSize);
	
}

void SelectCommandsAction::Execute()
{



	// notify the user
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	GameState* pState = pManager->GetGameState();
	Player* pCurrentPlayer = pState->GetCurrentPlayer();

	// hacking check
	if (pCurrentPlayer->IsHacked()) {
		pOut->PrintMessage("Your robot was hacked! Skipping your turn., click to continue");
		int x, y;
		pIn->GetPointClicked(x, y);
		pCurrentPlayer->SetHacked(false); // reset for next round
		pState->AdvanceCurrentPlayer();   // skip to next player
		pOut->ClearStatusBar();
		return;
	}

	// offering toolkit if the user has one 



	if (pCurrentPlayer->HasToolKitConsumable()) {
		pOut->PrintMessage("You have a Toolkit! Use it to repair? (Left=YES / Right=NO)");
		int x, y;
		pIn->GetPointClicked(x, y);
		if (x < UI.width / 2) {

			Consumable* pCon = pCurrentPlayer->GetInventoryItem(0);
			if (pCurrentPlayer->UseConsumable(pCon)) {
				pCon->UseEffect(pGrid, pState, pCurrentPlayer);
			}
		}
	}

		// offer hacking in acase the player has one
	if (pCurrentPlayer->HasHackDeviceConsumable()) {
			pOut->PrintMessage("You have a Hack Device! Use it on opponent? (Left=YES / Right=NO)");
			int x, y;
			pIn->GetPointClicked(x, y);
			if (x < UI.width / 2) {
				//
				Consumable* pCon = pCurrentPlayer->GetInventoryItem(1);
				if (pCurrentPlayer->UseConsumable(pCon)) {
					pCon->UseEffect(pGrid, pState, pCurrentPlayer);
				}

			}
	}

	ReadActionParameters();
		// notify the user
		pOut->PrintMessage("Commands saved. Click Execute Commands to continue.");
	}

SelectCommandsAction::~SelectCommandsAction()
{
}
