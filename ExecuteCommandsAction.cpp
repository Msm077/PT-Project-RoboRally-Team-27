#include "ExecuteCommandsAction.h"
#include "ShootingPhaseAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"
#include "Output.h"

//  Constructor / Destructor
ExecuteCommandsAction::ExecuteCommandsAction(ApplicationManager* pApp)
	: Action(pApp)
{
}

ExecuteCommandsAction::~ExecuteCommandsAction()
{
}

//  ReadActionParameters  -- nothing to read from the GUI

void ExecuteCommandsAction::ReadActionParameters()
{
	// No user input is needed before executing saved commands.
}

//  Execute
//
//  Called once per player turn.  Flow:
//
//  1. Guard: the current player must have commands saved.
//  2. Call Player::Move() -- executes saved commands one by one,
//     applies game-object effects after each step, applies Workshop
//     last (all handled inside Move).
//  3. Clear the hacked flag (defensive reset).
//  4. Advance the turn to the next player.
//  5. If the game ended during Move() (Flag reached, WaterPit, etc.)
//     return immediately.
//  6. If all players have now moved this round (IsRoundStart() is
//     true after AdvanceCurrentPlayer wraps), advance the phase
//     from MOVEMENT --> SHOOTING and run ShootingPhaseAction inline.
//     ShootingPhaseAction restores the phase to MOVEMENT when done.

void ExecuteCommandsAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	GameState* pGameState = pManager->GetGameState();
	Player* pPlayer = pGameState->GetCurrentPlayer();

	// 1. Guard
	if (pPlayer->GetSavedCommandCount() == 0)
	{
		pOut->PrintMessage("No commands to execute! Use 'Select Commands' first. Click...");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}

	// 2. Execute the player's saved commands
	pOut->PrintMessage("Executing commands -- watch your robot move!");
	pPlayer->Move(pGrid, pGameState);

	// 3. Clear hacked flag (defensive)
	pPlayer->SetHacked(false);

	//  4. Advance to the next player
	pGameState->AdvanceCurrentPlayer();

	// 5. Check if the game ended during Move() 
	if (pGameState->GetEndGame())
		return;

	// 6. Check if the full round is complete
	// IsRoundStart() returns true when currTurnIndex just wrapped
	// back to 0, meaning every player has moved once this round.
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