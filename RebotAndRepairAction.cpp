#include "RebotAndRepairAction.h"

#include "Player.h"
#include "Input.h"
#include<iostream>
#include"Grid.h"
#include "GameState.h"


void RebotAndRepairAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	GameState* pGS = pManager->GetGameState();

	Player* pCurrentPlayer = pManager->GetGameState()->GetCurrentPlayer();

	pCurrentPlayer->incrementHealth(1);


	pOut->PrintMessage("Current player cannot move, moving to the next player");
	pGS->AdvanceCurrentPlayer(pGrid);
}
