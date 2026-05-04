#include "Workshop.h"
#include "Player.h"
#include "Toolkit.h"
#include "HackDevice.h"
#include "DoubleLaser.h"

// ============================================================
//  Constructor / Destructor
// ============================================================

Workshop::Workshop(const CellPosition& workshopPosition)
    : GameObject(workshopPosition)
{
}

Workshop::~Workshop()
{
}

// ============================================================
//  Draw
// ============================================================

void Workshop::Draw(Output* pOut) const
{
    pOut->DrawWorkshop(position);
}

// ============================================================
//  Private helper: AskYesNo
//  Shows a message and waits for a click.
//  Left half of window = YES / Right half = NO.
// ============================================================

bool Workshop::AskYesNo(Grid* pGrid, const string& question) const
{
    Output* pOut = pGrid->GetOutput();
    Input*  pIn  = pGrid->GetInput();

    pOut->PrintMessage(question + "   [Left click = YES | Right click = NO]");

    int x, y;
    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();

    return (x < UI.width / 2); // left half = YES
}

// ============================================================
//  Apply
//  Called by Player::Move() only after ALL saved commands
//  in the round have been executed.
// ============================================================

void Workshop::Apply(Grid* pGrid, GameState* /*pState*/, Player* pPlayer)
{
    Output* pOut = pGrid->GetOutput();

    // ── Step 1: Repair the robot ──────────────────────────────
    pPlayer->SetHealth(10);
    pOut->PrintMessage("Workshop: Robot fully repaired! Click to continue...");
    int x, y;
    pGrid->GetInput()->GetPointClicked(x, y);
    pOut->ClearStatusBar();

    // ── Step 2: Offer Extended Memory device (permanent, one per player) ──
    if (pPlayer->GetDevice() == NO_DEVICE)
    {
        if (AskYesNo(pGrid, "Workshop: Buy Extended Memory? (+1 command slot, permanent)"))
        {
            pPlayer->SetDevice(EXTENDED_MEMORY);
            pOut->PrintMessage("Extended Memory equipped! You can now use 6 commands per round. Click...");
            pGrid->GetInput()->GetPointClicked(x, y);
            pOut->ClearStatusBar();
        }
    }

    // ── Step 3: Offer Toolkit consumable (one per inventory) ──
    if (!pPlayer->HasConsumableNamed("Toolkit"))
    {
        if (AskYesNo(pGrid, "Workshop: Buy Toolkit? (Repair robot anywhere, one-time use)"))
        {
            pPlayer->AddConsumable(new Toolkit());
            pOut->PrintMessage("Toolkit added to inventory! Use it before assigning commands. Click...");
            pGrid->GetInput()->GetPointClicked(x, y);
            pOut->ClearStatusBar();
        }
    }

    // ── Step 4: Offer Hack Device consumable ──────────────────
    if (!pPlayer->HasConsumableNamed("Hack Device"))
    {
        if (AskYesNo(pGrid, "Workshop: Buy Hack Device? (Force opponent to skip next turn, one-time use)"))
        {
            pPlayer->AddConsumable(new HackDevice());
            pOut->PrintMessage("Hack Device added to inventory! Use it before assigning commands. Click...");
            pGrid->GetInput()->GetPointClicked(x, y);
            pOut->ClearStatusBar();
        }
    }

    // ── Step 5: Offer Double Laser weapon ─────────────────────
    if (pPlayer->GetLaserDamage() < 2 && !pPlayer->HasConsumableNamed("Double Laser"))
    {
        if (AskYesNo(pGrid, "Workshop: Buy Double Laser? (Deal 2 damage in shooting phase, one-time upgrade)"))
        {
            pPlayer->AddConsumable(new DoubleLaser());
            pOut->PrintMessage("Double Laser added! It will activate automatically in the shooting phase. Click...");
            pGrid->GetInput()->GetPointClicked(x, y);
            pOut->ClearStatusBar();
        }
    }
}
