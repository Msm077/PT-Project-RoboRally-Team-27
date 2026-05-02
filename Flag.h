#pragma once
#include "GameObject.h"
class Flag :public GameObject
{
public:
	Flag(const CellPosition & flagposition); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a flag in a selected cell
	void Save(ofstream& OutFile, Type t);
	void Read(ifstream& Infile);
	bool IsObject(Type t);
	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the flag
	virtual ~Flag(); // Virtual destructor
};