#pragma once
#include "Action.h"

// ============================================================
// SelectCommandsAction  (Play Mode)
//
// Responsibilities:
//   1. Check if the current player is hacked -- if so, skip turn.
//   2. Offer any consumables in the player's inventory BEFORE
//      commands are assigned (Toolkit, HackDevice).
//      DoubleLaser is deferred to the Shooting Phase.
//   3. Generate a fresh random command pool and let the player
//      pick Min(MaxCommands, health) commands.
// ============================================================
class SelectCommandsAction : public Action
{
public:

    SelectCommandsAction(ApplicationManager* pApp);

    // Generates the random pool and reads the player's command choices
    virtual void ReadActionParameters() override;

    // Runs the full sequence: hacked-check -> consumables -> ReadActionParameters
    virtual void Execute() override;

    virtual ~SelectCommandsAction();
};
