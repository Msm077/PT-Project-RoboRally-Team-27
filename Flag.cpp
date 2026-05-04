#include "Flag.h"
Flag::Flag(const CellPosition & flagposition) : GameObject(flagposition)
{

}

void Flag::Draw(Output* pOut) const
{
	pOut->DrawFlag(position);
}

void Flag::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	 int playerNum = pPlayer->GetPlayerNumber();
    string msg = "Player " + to_string(playerNum) + " has reached the flag! Player " + 
                 to_string(playerNum) + " wins! Click On either: New Game, To Design Mode, Exit ...";
    pGrid->PrintErrorMessage(msg);
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);
	pState->SetEndGame(true);

    //pState->EndGame(playerNum);
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a flag. Click to continue ..." and wait mouse click

	// 2- Apply the flag's effect by ending the game
	//    Review the "pGrid" functions and decide which function can be used for that
}
GameObject* Flag::Photocopy(const CellPosition& newPos) const
{
	return new Flag (newPos);
}
void Flag::Save(ofstream& OutFile, Type t) {
	if (IsObject(t)) {
		OutFile << position.GetCellNum() << endl;
	}
	else {
		return;
	}
}

void Flag::Read(ifstream& Infile) {
	int x1;
	Infile >> x1;
	position = x1;

}

bool Flag::IsObject(Type t) {
	if (t == Flags) {
		return 1;
	}
	return 0;
}

Flag::~Flag()
{

}
