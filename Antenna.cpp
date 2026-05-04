#include "Antenna.h"
#include "GameState.h"
#include "Player.h"



Antenna::Antenna(const CellPosition & antennaPosition):GameObject(antennaPosition)
{
}

void Antenna::Draw(Output * pOut) const
{
	pOut->DrawAntenna(position);
}

void Antenna::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("The antenna will decide the turn of players. Click to continue ...");
	int x;
	int y;
	pIn->GetPointClicked(x, y);
	int minDistance = -1;
	int firstPlayer = 0;
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		Player* p = pState->GetPlayer(i);
		CellPosition playerPos = p->GetCell()->GetCellPosition();

		int dV = abs(playerPos.VCell() - position.VCell());
		int dH = abs(playerPos.HCell() - position.HCell());
		int distance = dV + dH;

		if (minDistance == -1 || distance < minDistance)
		{
			minDistance = distance;
			firstPlayer = i;
		}
		pState->SetFirstPlayer(firstPlayer);

		pOut->PrintMessage("Player " + to_string(firstPlayer + 1) + " will play first. Click to continue ...");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "the antenna will decide the turn of players. Click to continue ..." and wait mouse click

	// 2- Determine turn order based on each player's distance from the antenna.
	//    Hint: distance = |dV| + |dH|
	//    The player closest to the antenna plays first. Ties are broken by player number.
	//    Use pState to update the turn order accordingly.
	// 3- Print a message indicating which player will play first

}

GameObject* Antenna::Photocopy(const CellPosition& newPos) const
{
	return new Antenna(newPos) ;
}

void Antenna::Save(ofstream& OutFile, Type t) {
	if (IsObject(t)) {
		OutFile << position.GetCellNum() << endl;
	}
	else {
		return;
	}
}

void Antenna::Read(ifstream& Infile) {
	int x1;
		Infile >> x1;
		position = x1;
	
}


bool Antenna::IsObject(Type t) {
	if (t == Antennas) {
		return 1;
	}
	return 0;
}
Antenna::~Antenna()
{
}
