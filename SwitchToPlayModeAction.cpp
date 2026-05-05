#include "SwitchToPlayModeAction.h"
#include "Grid.h"
#include "GameState.h"
#include "Output.h"

SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchToPlayModeAction::ReadActionParameters()
{
	// No parameters needed -- a mode switch requires no user input
}

void SwitchToPlayModeAction::Execute()
{
	
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	GameState* pState = pManager->GetGameState();
	if (pGrid->GetNumberofObject(Flags) == 1 && pGrid->GetNumberofObject(Antennas) == 1) { //Check if the game is Playable (Added Recently)
		// 1. Switch the global interface mode to Play Mode
		UI.InterfaceMode = MODE_PLAY;

		// 2. Redraw the toolbar with Play Mode buttons
		pOut->CreatePlayModeToolBar();

		// 3. Reset game state for the new play session
		pState->SetCurrentPhase(PHASE_MOVEMENT);
		pState->ResetAllPlayers();
		// 4. Redraw the full interface (board + player info bar)
		pManager->UpdateInterface();
	}
	else {
		pOut->PrintMessage("You must have a Flag and an Antenna to launch the game");
			return;
	}
	///TODO: Add any other initialisation needed when entering Play Mode.
}

SwitchToPlayModeAction::~SwitchToPlayModeAction()
{
}
