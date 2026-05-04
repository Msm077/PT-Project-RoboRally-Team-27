#pragma once

#include "Grid.h"
#include "Cell.h"
#include "DEFS.h"

// Forward declarations
class GameState;
<<<<<<< Updated upstream
class Consumable;  // abstract base -- Player owns Consumable* pointers
=======
class Consumable; // abstract base class for inventory items
>>>>>>> Stashed changes

class Player
{
	Cell* pCell;           // Pointer to the cell the player currently occupies
	const int playerNum;   // Player index 0..MaxPlayerCount-1 (constant after construction)
	Cell* startCell;

	Direction currDirection; // The direction the player is currently facing
	int health;              // Player's current health points

<<<<<<< Updated upstream
	// ---- Saved Commands (the player's "program" for this round) ----
=======
	// ---- Saved Commands ----
>>>>>>> Stashed changes
	Command savedCommands[MaxSavedCommands];
	int savedCommandCount;
	void ExecuteCommand(Command cmd, CellPosition& pos);

<<<<<<< Updated upstream
	// ---- Hacked flag (Hack Device consumable) ----
=======
	// ---- Hacked flag (HackDevice consumable) ----
>>>>>>> Stashed changes
	bool isHacked; // true = this player skips their turn this round

	// ---- Permanent device (Extended Memory) ----
	DeviceType equippedDevice;

<<<<<<< Updated upstream
	// ---- Laser (Shooting Phase) ----
	// Default = 1 (basic laser); set to 2 when DoubleLaser consumable is used.
	int laserDamage;

	// ---- Consumable inventory ----
	// Owns Consumable* pointers (polymorphic).
	// Player is responsible for deleting them when used or on destruction.
=======
	// ---- Laser damage (Shooting Phase) ----
	// Default = 1 (basic laser); set to 2 when DoubleLaser is activated.
	int laserDamage;

	// ---- Consumable inventory ----
	// Holds Consumable* pointers polymorphically.
	// Player owns these and deletes them in the destructor if unused.
>>>>>>> Stashed changes
	Consumable* inventory[MaxConsumables];
	int inventoryCount;

public:

<<<<<<< Updated upstream
	Player(Cell* pCell, int playerNum); // Initialises all data members
	~Player();                          // Deletes remaining unused consumables
=======
	Player(Cell* pCell, int playerNum);
	~Player(); // deletes any remaining consumables in inventory
>>>>>>> Stashed changes

	// ====== Setters and Getters ======

	void  SetCell(Cell* cell);
	Cell* GetCell() const;

	void SetHealth(int h);
	int  GetHealth() const;

	Direction GetDirection() const;
	void      SetDirection(Direction d);

	// ====== Saved Commands ======

<<<<<<< Updated upstream
	void    AddSavedCommand(Command cmd);
	void    ClearSavedCommands();
	int     GetSavedCommandCount() const;
	Command GetSavedCommand(int index) const;
=======
	void     AddSavedCommand(Command cmd);
	void     ClearSavedCommands();
	int      GetSavedCommandCount() const;
	Command  GetSavedCommand(int index) const;
>>>>>>> Stashed changes
	Command* GetSavedCommands();

	// ====== Drawing ======

	void Draw(Output* pOut) const;
	void ClearDrawing(Output* pOut) const;

	// ====== Game Logic ======

	void Move(Grid* pGrid, GameState* pState);

	void AppendPlayerInfo(string& playersInfo) const;

<<<<<<< Updated upstream
	void incrementHealth(); // +1 health (used by Reboot & Repair action)

	// ====== Device (Extended Memory) ======

	int        GetMaxCommands() const; // returns 5 normally, 6 with Extended Memory
=======
	void incrementHealth(); // +1 health (used by Reboot & Repair)

	// ====== Device (Extended Memory) ======

	int        GetMaxCommands() const; // 5 normally, 6 with Extended Memory
>>>>>>> Stashed changes
	void       SetDevice(DeviceType d);
	DeviceType GetDevice() const;

	// ====== Consumable Inventory ======
<<<<<<< Updated upstream
	// Player takes ownership of the Consumable* pointer passed to AddConsumable().

	void AddConsumable(Consumable* pConsumable); // Add to inventory (takes ownership)

	// Removes and RETURNS the first consumable of the given runtime type
	// matching predicate T. Caller becomes owner and must delete it after use.
	// Returns nullptr if not found.
	// Usage: the action calls UseConsumableByName() which wraps this.
	Consumable* RemoveConsumable(int index); // Remove by slot index, returns pointer

=======
	// Player takes ownership of every Consumable* passed to AddConsumable().

	void        AddConsumable(Consumable* pConsumable); // add to inventory (takes ownership)
	Consumable* RemoveConsumable(int index);            // remove by slot, caller must delete
>>>>>>> Stashed changes
	bool        HasConsumableNamed(const string& name) const;
	int         FindConsumable(const string& name) const; // returns index or -1
	int         GetInventoryCount() const;
	Consumable* GetConsumable(int index) const;

	// ====== Laser / Shooting Phase ======

	int  GetLaserDamage() const;
	void SetLaserDamage(int damage);

<<<<<<< Updated upstream
	// Returns true if this robot is directly facing pOpponent
	// in the same row or column with no grid boundary in between.
=======
	// True if this robot directly faces pOpponent in the same row or column.
>>>>>>> Stashed changes
	bool IsFacingPlayer(const Player* pOpponent) const;

	// ====== Hacked flag ======

	void SetHacked(bool hacked);
	bool IsHacked() const;
<<<<<<< Updated upstream
};
=======

	void Reset();
};
>>>>>>> Stashed changes
