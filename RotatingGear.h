#pragma once
#include "GameObject.h"
class RotatingGear : public GameObject
{
	bool isClockWise; // if it is true then direction is clockwise, if it is false then direction is anticlockwise
public:
	RotatingGear(const CellPosition & gearposition,bool clockwise); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a rotating gear in a selected cell
	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the rotating gear
	void Save(ofstream& OutFile, Type t);
	bool GetisClockWise() const; // Getter for the direction
	bool IsObject(Type t);
	virtual GameObject* Photocopy(const CellPosition& newPos) const;

	virtual ~RotatingGear();
};

