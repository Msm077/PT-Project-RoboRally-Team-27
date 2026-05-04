#pragma once
#include "Consumable.h"

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
