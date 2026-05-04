#pragma once
using namespace std;
#include<iostream>


#pragma once
#include <iostream>
#include <string> // Add this line
using namespace std;


// Forward declarations
class Grid;
class GameState;
class Player;

// Consumable  (abstract base class)
//
// Represents a one-time-use item a player can carry and spend
// before assigning movement commands each round.
//
// Subclasses:
//   Toolkit    -- instantly repairs the robot to full health
//   HackDevice -- forces the opponent to skip their next turn


class Consumable
{
public:

    virtual ~Consumable() {}

    // Returns a short display name shown in status messages, e.g. "Toolkit"
    virtual string GetName() const = 0;

    // Applies this consumable's one-time effect.
    // The caller (SelectCommandsAction) invokes this, then deletes the object.
    virtual void UseEffect(Grid* pGrid, GameState* pState, Player* pPlayer) = 0;
};

