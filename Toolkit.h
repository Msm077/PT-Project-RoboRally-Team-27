#pragma once
#include "Consumable.h"
<<<<<<< Updated upstream

// ============================================================
// Toolkit  (Consumable subclass)
//
// One-time use. When spent before assigning commands, the robot
// is fully repaired to maximum health (10) without needing to
// visit a Workshop cell.
// ============================================================
=======
>>>>>>> Stashed changes
class Toolkit : public Consumable
{
public:

    virtual string GetName() const override;

    // Restores the player's health to the maximum (10).
    virtual void UseEffect(Grid* pGrid, GameState* pState, Player* pPlayer) override;

    virtual ~Toolkit() {}
};
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
