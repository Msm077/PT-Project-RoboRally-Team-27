#include "NewGameAction.h"



NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void NewGameAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


}


void NewGameAction::Execute()
{
	ReadActionParameters();
	
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	GameState* pState = pManager->GetGameState();
	
	pState->ResetAllPlayers();
	
	pOut->ClearStatusBar();
	pGrid->UpdateInterface(pState);
	

	


}

NewGameAction::~NewGameAction()
{
}
