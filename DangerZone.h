#pragma once
#include "GameObject.h"
class DangerZone:public GameObject
{
public:
	DangerZone(const CellPosition & dangerZonePosition);
	virtual void Draw(Output* pOut) const; // Draws a danger zone in the cell
	virtual GameObject* Photocopy(const CellPosition& newPos) const;

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the danger zone

	void Save(ofstream& OutFile, Type t);
	bool IsObject(Type t);
	virtual ~DangerZone();
};

