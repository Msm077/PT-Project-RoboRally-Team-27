#include "ShootingPhaseAction.h"
#include "Player.h"
#include "GameState.h"
#include "Grid.h"
#include "Consumable.h"
#include "DoubleLaser.h"
<<<<<<< Updated upstream
#include <string>
using namespace std;

// ============================================================
//  Constructor / Destructor
// ============================================================
=======
#include "ApplicationManager.h"

using namespace std;

//  Constructor / Destructor
>>>>>>> Stashed changes

ShootingPhaseAction::ShootingPhaseAction(ApplicationManager* pApp)
    : Action(pApp)
{
}

ShootingPhaseAction::~ShootingPhaseAction()
{
}

// ============================================================
//  ReadActionParameters  (nothing to read -- fully automatic)
// ============================================================

void ShootingPhaseAction::ReadActionParameters()
{
    // No user input required for the shooting phase
}

// ============================================================
//  Helper: activate DoubleLaser if present in inventory
//  Returns true if the laser was upgraded this call.
// ============================================================

static bool ActivateDoubleLaserIfPresent(Player* pPlayer)
{
    int idx = pPlayer->FindConsumable("Double Laser");
    if (idx == -1)
        return false;

    // Remove from inventory and apply the effect immediately
    Consumable* pLaser = pPlayer->RemoveConsumable(idx);
    // UseEffect sets laserDamage = 2 on the player (no grid/state needed for that)
    // We call it directly; pGrid/pState are nullptr because DoubleLaser only calls
    // SetLaserDamage -- but we pass real pointers to be safe.
    // Actually we have no grid here; delegate via the method that only needs player:
    pPlayer->SetLaserDamage(2);
    delete pLaser; // consumed
    return true;
}

// ============================================================
//  Execute
// ============================================================

void ShootingPhaseAction::Execute()
{
    ReadActionParameters();

<<<<<<< Updated upstream
    Grid*      pGrid  = pManager->GetGrid();
    Output*    pOut   = pGrid->GetOutput();
    Input*     pIn    = pGrid->GetInput();
=======
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
>>>>>>> Stashed changes
    GameState* pState = pManager->GetGameState();

    pOut->PrintMessage("--- Shooting Phase ---  Click to begin...");
    int x, y;
    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();

    // Each player shoots in turn order (two-player game: player 0 then player 1)
    for (int shooterIdx = 0; shooterIdx < MaxPlayerCount; shooterIdx++)
    {
<<<<<<< Updated upstream
        Player* pShooter  = pState->GetPlayer(shooterIdx);
=======
        Player* pShooter = pState->GetPlayer(shooterIdx);
>>>>>>> Stashed changes
        Player* pOpponent = nullptr;

        // Find the opponent (the other player)
        for (int j = 0; j < MaxPlayerCount; j++)
        {
            if (j != shooterIdx)
            {
                pOpponent = pState->GetPlayer(j);
                break;
            }
        }

        if (!pOpponent) continue;

        // ── Activate DoubleLaser if the shooter has one ───────────────
        bool upgraded = ActivateDoubleLaserIfPresent(pShooter);
        if (upgraded)
        {
            pOut->PrintMessage("Player " + to_string(shooterIdx + 1) +
<<<<<<< Updated upstream
                               " activates Double Laser! Click to continue...");
=======
                " activates Double Laser! Click to continue...");
>>>>>>> Stashed changes
            pIn->GetPointClicked(x, y);
            pOut->ClearStatusBar();
        }

        // ── Check if shooter is directly facing the opponent ──────────
        if (pShooter->IsFacingPlayer(pOpponent))
        {
            int damage = pShooter->GetLaserDamage();
            int newHealth = pOpponent->GetHealth() - damage;
            if (newHealth < 0) newHealth = 0;
            pOpponent->SetHealth(newHealth);

            pOut->PrintMessage("Player " + to_string(shooterIdx + 1) +
<<<<<<< Updated upstream
                               " hits Player " + to_string((shooterIdx == 0) ? 2 : 1) +
                               " for " + to_string(damage) + " damage! " +
                               "Opponent health: " + to_string(newHealth) +
                               "  Click to continue...");
=======
                " hits Player " + to_string((shooterIdx == 0) ? 2 : 1) +
                " for " + to_string(damage) + " damage! " +
                "Opponent health: " + to_string(newHealth) +
                "  Click to continue...");
>>>>>>> Stashed changes
            pIn->GetPointClicked(x, y);
            pOut->ClearStatusBar();

            // ── Check winning condition after hit ─────────────────
            if (newHealth <= 0)
            {
                pOut->PrintMessage("Player " + to_string(shooterIdx + 1) +
<<<<<<< Updated upstream
                                   " wins! Opponent robot destroyed. Click...");
=======
                    " wins! Opponent robot destroyed. Click...");
>>>>>>> Stashed changes
                pIn->GetPointClicked(x, y);
                pOut->ClearStatusBar();
                pState->SetEndGame(true);
                return; // stop shooting
            }
        }
        else
        {
            pOut->PrintMessage("Player " + to_string(shooterIdx + 1) +
<<<<<<< Updated upstream
                               " fires -- no target in line of sight. Click...");
=======
                " fires -- no target in line of sight. Click...");
>>>>>>> Stashed changes
            pIn->GetPointClicked(x, y);
            pOut->ClearStatusBar();
        }

        // Reset laser damage back to 1 for next round
        // (DoubleLaser is a one-time-use weapon, already removed from inventory above)
        pShooter->SetLaserDamage(1);
    }

    // ── Advance back to Movement phase for next round ─────────────
    pState->AdvancePhase(); // SHOOTING -> MOVEMENT
<<<<<<< Updated upstream
}
=======
}
>>>>>>> Stashed changes
