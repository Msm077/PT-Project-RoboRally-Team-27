#pragma once
#include "GameObject.h"

// ============================================================
// Workshop  (GameObject subclass)
//
// When a player's robot lands on a Workshop cell:
//   1. The robot is fully repaired (health restored to 10).
//   2. The player is offered purchasable upgrades:
//        a. Extended Memory device  -- +1 command slot per round (permanent)
//        b. Toolkit consumable      -- repair anywhere, one-time use
//        c. Hack Device consumable  -- skip opponent's next turn, one-time use
//        d. Double Laser weapon     -- deal 2 damage in shooting phase, one-time use
//
// Each offer is a yes/no choice: left half of screen = YES, right = NO.
// Workshop is applied only AFTER all saved movement commands in a round
// have been executed (handled by Player::Move()).
// ============================================================
class Workshop : public GameObject
{
public:

    Workshop(const CellPosition& workshopPosition);

    virtual void Draw(Output* pOut) const;

    virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer);

    virtual ~Workshop();

private:

    // Helper: prompt the player with a yes/no question and return true if YES.
    // YES = click on the left half of the window; NO = right half.
    bool AskYesNo(Grid* pGrid, const string& question) const;
};
