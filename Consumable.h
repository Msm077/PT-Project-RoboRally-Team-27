#pragma once
#include <string>
using namespace std;

// Forward declarations
class Grid;
class GameState;
class Player;

// ============================================================
// Consumable  (abstract base class)
//
// Represents a one-time-use item a player can carry and spend
// before assigning movement commands each round.
//
// Subclasses:
//   Toolkit    -- instantly repairs the robot to full health
//   HackDevice -- forces the opponent to skip their next turn
//   DoubleLaser-- weapon: deals 2 damage instead of 1 (shooting phase)
//
// OOP design note:
//   Player owns an array of Consumable* pointers so it can store
//   any mix of subclasses without knowing their concrete types.
//   UseEffect() is the polymorphic hook called when the player
//   decides to spend the item.
// ============================================================
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
