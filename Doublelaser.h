#pragma once
#include "Consumable.h"

// ============================================================
// DoubleLaser  (Consumable / Weapon subclass)
//
// Purchased at a Workshop. Unlike Toolkit and HackDevice this
// item is NOT consumed before the command-selection phase.
// Instead it upgrades the player's laser damage from 1 to 2
// for the shooting phase that follows movement each round.
//
// It is still modelled as a Consumable so the Player inventory
// can hold it polymorphically; UseEffect() upgrades laserDamage
// and removes the item from inventory (one upgrade only).
// ============================================================
class DoubleLaser : public Consumable
{
public:

    virtual string GetName() const override;

    // Sets the player's laser damage to 2.
    // Called during the Shooting Phase (ShootingPhaseAction) or
    // at Workshop purchase time -- either way it is one-time-use.
    virtual void UseEffect(Grid* pGrid, GameState* pState, Player* pPlayer) override;

    virtual ~DoubleLaser() {}
};
