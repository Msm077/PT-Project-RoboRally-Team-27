#pragma once
// HackDevice  (Consumable subclass)
//
// One-time use. When spent before assigning commands, the
// opponent's robot is hacked: they are forced to skip their
// entire turn in the current round (no command selection,
// no movement execution).


#include "Consumable.h"
class HackDevice : public Consumable
{
public:

    virtual string GetName() const override;

    // Marks the OPPONENT player as hacked so SelectCommandsAction
    // skips their turn when it runs.
    virtual void UseEffect(Grid* pGrid, GameState* pState, Player* pPlayer) override;

    virtual ~HackDevice() {}
};
