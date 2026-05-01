#pragma once
#include "GameObject.h"
class Antenna :public GameObject
{
public:
	Antenna(const CellPosition & antennaPosition);
	virtual void Draw(Output* pOut) const; // Draws an antenna

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the antenna

	void Save(ofstream& OutFile, Type t);
	bool IsObject(Type t);
	virtual ~Antenna();
};

