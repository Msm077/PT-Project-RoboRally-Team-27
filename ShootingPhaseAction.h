#pragma once
#include "Action.h"

// ============================================================
// ShootingPhaseAction  (Play Mode -- Bonus)
//
// Called after BOTH players have executed their movement commands
// for the round (i.e. after ExecuteCommandsAction for Player 2).
//
// Sequence for each player (in turn order):
//   1. Check if this robot is directly facing the opponent in
//      the same row or column (Player::IsFacingPlayer()).
//   2. If the DoubleLaser consumable is in inventory, use it
//      automatically (upgrades laserDamage to 2, removes item).
//   3. If facing: fire -- reduce opponent health by laserDamage.
//      Print a message and wait for a click.
//   4. If opponent health reaches 0, the firing player wins.
//
// ApplicationManager calls this action when GameState's current
// phase == PHASE_SHOOTING (after AdvancePhase() from ExecuteCommandsAction).
// ============================================================
class ShootingPhaseAction : public Action
{
public:

    ShootingPhaseAction(ApplicationManager* pApp);

    virtual void ReadActionParameters() override; // Nothing to read from GUI

    virtual void Execute() override;

    virtual ~ShootingPhaseAction();
};
