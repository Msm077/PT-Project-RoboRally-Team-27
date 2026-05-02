#include "Workshop.h"



Workshop::Workshop(const CellPosition & workshopPosition):GameObject( workshopPosition)
{

}


void Workshop::Draw(Output * pOut) const
{
	pOut->DrawWorkshop(position);
}

void Workshop::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	///TODO: Implement this function
	// Apply the workshop's effect on the player
	// [OPTIONAL BONUS] Consumables can be given to the player here
}
void Workshop::Save(ofstream& OutFile, Type t) {
	if (t == WorkShops) {
		OutFile << position.GetCellNum() << endl;
	}
	else {
		return;
	}
}

void Workshop::Read(ifstream& Infile) {
	int x1;
	
		Infile >> x1;
		position = x1;
	
	
}
bool Workshop::IsObject(Type t) {
	if (t == WorkShops) {
		return 1;
	}
	return 0;
}

Workshop::~Workshop()
{
}
