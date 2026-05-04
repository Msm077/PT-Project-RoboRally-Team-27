#include "ExecuteCommandsAction.h"
#include "ApplicationManager.h"
#include "ShootingPhaseAction.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"
#include "Output.h"

ExecuteCommandsAction::ExecuteCommandsAction(ApplicationManager* pApp) : Action(pApp)
{
}

void ExecuteCommandsAction::ReadActionParameters()
{
	// No parameters to read from the user for execution.
}

void ExecuteCommandsAction::Execute()
{
	// 1. Get necessary pointers
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	GameState* pGameState = pManager->GetGameState();
	

	// 2. Get the current player
	Player* pCurrentPlayer = pGameState->GetCurrentPlayer();

	// 3. Check if the player has any commands saved
	if (pCurrentPlayer->GetSavedCommandCount() == 0)
	{
		pOut->PrintMessage("No commands selected! Please select commands first.");
		return;
	}

	// 4. Trigger the Move logic you wrote
	pOut->PrintMessage("Executing Commands... Watch the player move!");
	pCurrentPlayer->Move(pGrid, pGameState);

	// Reset hacked state after turn ends
	pCurrentPlayer->SetHacked(false); //HANDLED IN SELECT COMMANDS ACTION



	// 5. Advance to the next player's turn AND CLEAR COMMANDS
	pCurrentPlayer->ClearSavedCommands();
	pGameState->AdvanceCurrentPlayer();
	if (pGameState->GetEndGame())
		return;
	// 6. Update UI
	pOut->PrintMessage("Turn ended. Next player's turn.");
}

ExecuteCommandsAction::~ExecuteCommandsAction()
{
	GameState* pGameState = pManager->GetGameState();
	if (pGameState->IsRoundStart())
	{
		// Move to the shooting phase
		pGameState->AdvancePhase(); // MOVEMENT --> SHOOTING

		// Run the shooting phase immediately (no toolbar click needed)
		ShootingPhaseAction shootAction(pManager);
		shootAction.Execute();
		// ShootingPhaseAction::Execute() calls AdvancePhase() at the
		// end: SHOOTING --> MOVEMENT, so the next round starts cleanly.
	}
}