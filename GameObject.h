#pragma once

#include "Grid.h"
#include <fstream>

// Forward declarations
class Player;
class GameState;

// Base class for all game objects (Belt, Flag, WaterPit, DangerZone, RotatingGear, Workshop, Antenna).
class GameObject
{
protected:
	CellPosition position; // The cell this object occupies

public:

	GameObject(const CellPosition& pos);

	CellPosition GetPosition() const;

	// ============ Virtual Functions ============

	virtual void Draw(Output* pOut) const = 0;

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer) = 0;
	void SetPosition(const CellPosition& pos) { position = pos; }
	// Save / Load (uncomment and implement in derived classes when needed):
	virtual void Save(ofstream& OutFile, Type t) = 0;
	//virtual void Read(ifstream& Infile)  = 0;
	virtual bool IsObject(Type t) = 0;
	virtual ~GameObject();
};
