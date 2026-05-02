#pragma once
#include "GameObject.h"
class WaterPit:public GameObject
{
public:
	WaterPit(const CellPosition & waterPitPosition); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a water pit in the cell

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the water pit

	void Save(ofstream& OutFile, Type t);
	void Read(ifstream& Infile);
	bool IsObject(Type t);
	virtual ~WaterPit();
};

