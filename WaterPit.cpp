#include "WaterPit.h"



WaterPit::WaterPit(const CellPosition & waterPitPosition):GameObject(waterPitPosition)
{
}

void WaterPit::Draw(Output * pOut) const
{
	pOut->DrawWaterPit(position);
}

GameObject* WaterPit::Photocopy(const CellPosition& newPos) const
{
	return new WaterPit(newPos);
}

void WaterPit::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
int playerNum = pPlayer->GetPlayerNumber();
    pGrid->PrintErrorMessage("Player " + to_string(playerNum) + " fell into a water pit! Click to continue...");
    
	pPlayer->incrementHealth(-3);
            int winnerNum;

    if (pPlayer->GetHealth() <= 0)
    {
        pGrid->PrintErrorMessage("Player " + to_string(playerNum) + " has died! Game over. Click to continue...");
		pState->SetEndGame(true);
		int x, y;
		pGrid->GetInput()->GetPointClicked(x, y);
    if (playerNum == 0)
        winnerNum = 1;
    else
        winnerNum = 0;
       
    }
    else
    {
        pPlayer->SetCell(pGrid->GetStartCell());
		Draw(pGrid->GetOutput());
		pState->DrawAllPlayers(pGrid->GetOutput());
        pGrid->PrintErrorMessage("Player " + to_string(playerNum) + " returns to start with " + to_string(pPlayer->GetHealth()) + " health. Click to continue...");
    }

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message, make sure to edit this message according to which player wins "You drowned in a water pit. Player (0/1) wins !  Click to continue ..." and wait mouse click

	// 2- Apply the water pit's effect by setting the player's health which drowned to zero and ending the game
	// 3- Update the players info which is displayed (check Grid class and decide which function to use)
}

void WaterPit::Save(ofstream& OutFile, Type t) {
	if (IsObject(t)) {
		OutFile << position.GetCellNum() << endl;
	}
	else {
		return;
	}
}

void WaterPit::Read(ifstream& Infile) {
	int x1;
	Infile >> x1;
	position = x1;
	
	
}

bool WaterPit::IsObject(Type t) {
	if (t == WaterPits) {
		return 1;
	}
	return 0;
}

WaterPit::~WaterPit()
{
}
