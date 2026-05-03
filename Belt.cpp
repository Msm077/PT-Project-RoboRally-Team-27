#include "Belt.h"


Belt::Belt(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}
void Belt::Draw(Output* pOut) const
{
	pOut->DrawBelt(position, endCellPos);
}

void Belt::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a belt. Click to continue ..." and wait mouse click

	// 2- Apply the belt's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that

}
CellPosition Belt::GetEndPosition() const
{
	return endCellPos;
}

GameObject* Belt::Photocopy(const CellPosition& newPos) const
{
	int offsetV = endCellPos.VCell() - position.VCell();
	int offsetH = endCellPos.HCell() - position.HCell();

	CellPosition newEndPos(newPos.VCell() + offsetV, newPos.HCell() + offsetH);

	if (!newEndPos.IsValidCell())
		return nullptr;

	return new Belt(newPos, newEndPos);
}

void Belt::Save(ofstream& OutFile, Type t) {
	if (IsObject(t)) {
		OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
	}
	else {
		return;
	}
}
void Belt::Read(ifstream& Infile) {
	int x1 , x2;
		Infile >> x1 >> x2;
		position = x1;
		endCellPos = x2;
	
}
bool Belt::IsObject(Type t) {
	if (t == Belts) {
		return 1;
	}
	return 0;
}
Belt::~Belt()
{
}
