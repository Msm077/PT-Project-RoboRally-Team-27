#pragma once
#include "GameObject.h"
#include "Player.h"
#include "GameState.h"
class WaterPit:public GameObject
{
public:
	WaterPit(const CellPosition & waterPitPosition); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a water pit in the cell
	 GameObject* Photocopy(const CellPosition& newPos) const;

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the water pit

	void Save(ofstream& OutFile, Type t);
	void Read(ifstream& Infile);
	bool IsObject(Type t);
	virtual ~WaterPit();
};

