#include "RotatingGear.h"




RotatingGear::RotatingGear(const CellPosition & gearposition,bool clockwise) : GameObject(gearposition)
{
	isClockWise = clockwise;
}

void RotatingGear::Draw(Output* pOut) const
{
	pOut->DrawRotatingGear(position, isClockWise);
}

void RotatingGear::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message and change the message according to direction of rotation "You have reached a rotating gear, you will rotate (clockwise/ anti-clockwise) Click to continue ..." and wait mouse click
	//2- Apply the roating gear's effect by rotating the player according to the direction
}
bool RotatingGear::GetisClockWise() const
{
	return isClockWise;
}

void RotatingGear::Save(ofstream& OutFile, Type t) {
	if (t == RotatingGears) {
		OutFile << position.GetCellNum() << " " << this->GetisClockWise() << endl;
	}
	else {
		return;
	}
}

void RotatingGear::Read(ifstream& Infile) {
	int x1;
	bool b1;
	
		Infile >> x1 >> b1;
		position = x1;
		isClockWise = b1;
	
}

bool RotatingGear::IsObject(Type t) {
	if (t == RotatingGears) {
		return 1;
	}
	return 0;
}
RotatingGear::~RotatingGear()
{
}
