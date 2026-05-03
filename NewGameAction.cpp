#include "NewGameAction.h"



NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void NewGameAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	UI.InterfaceMode = MODE_DESIGN;

}


void NewGameAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();
	//pGrid->ClearGrid();
	pGrid->UpdateInterface(pState);

	


}

NewGameAction::~NewGameAction()
{
}
