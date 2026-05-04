#include "SelectCommandsAction.h"
#include "Player.h"
#include "Consumable.h"
#include "Grid.h"
#include "GameState.h"
#include <string>
using namespace std;

// ============================================================
//  Constructor / Destructor
// ============================================================

SelectCommandsAction::SelectCommandsAction(ApplicationManager* pApp)
    : Action(pApp)
{
}

SelectCommandsAction::~SelectCommandsAction()
{
}

// ============================================================
//  Helper: map Command enum to readable name
// ============================================================

static string GetCommandName(Command cmd)
{
    switch (cmd)
    {
    case MOVE_FORWARD_ONE_STEP:     return "Move Forward 1";
    case MOVE_FORWARD_TWO_STEPS:    return "Move Forward 2";
    case MOVE_FORWARD_THREE_STEPS:  return "Move Forward 3";
    case MOVE_BACKWARD_ONE_STEP:    return "Move Backward 1";
    case MOVE_BACKWARD_TWO_STEPS:   return "Move Backward 2";
    case MOVE_BACKWARD_THREE_STEPS: return "Move Backward 3";
    case ROTATE_CLOCKWISE:          return "Rotate Clockwise";
    case ROTATE_COUNTERCLOCKWISE:   return "Rotate Counter-Clockwise";
    default:                        return "No Command";
    }
}

// ============================================================
//  Helper: offer each consumable to the player BEFORE
//          they assign their movement commands for this round.
//
//  Design note:
//    The spec says consumables "appear in the action menu
//    BEFORE assigning the commands."  We therefore call this
//    helper at the START of Execute(), before ReadActionParameters()
//    fills the saved-command slots.
//
//    Each consumable is offered once.  If the player says YES:
//      - RemoveConsumable() pulls it out of inventory (Player
//        gives up ownership of the pointer).
//      - UseEffect() is called (polymorphic -- correct subclass runs).
//      - The pointer is then deleted here (one-time use).
// ============================================================

static void OfferConsumables(Grid* pGrid, GameState* pState, Player* pPlayer)
{
    Output* pOut = pGrid->GetOutput();
    Input*  pIn  = pGrid->GetInput();

    int count = pPlayer->GetInventoryCount();
    if (count == 0)
        return; // nothing to offer

    // Iterate by index; note count may shrink as items are used
    for (int i = 0; i < pPlayer->GetInventoryCount(); /* manual increment */)
    {
        Consumable* pC = pPlayer->GetConsumable(i);
        if (!pC) { i++; continue; }

        // DoubleLaser is a weapon -- it activates automatically in the
        // shooting phase, not here.  Skip offering it manually.
        if (pC->GetName() == "Double Laser") { i++; continue; }

        string question = "You have a " + pC->GetName() +
                          "! Use it now?  [Left = YES | Right = NO]";
        pOut->PrintMessage(question);

        int x, y;
        pIn->GetPointClicked(x, y);
        pOut->ClearStatusBar();

        bool usedIt = (x < UI.width / 2); // left half = YES
        if (usedIt)
        {
            // Remove from inventory (Player gives up ownership)
            Consumable* spent = pPlayer->RemoveConsumable(i);
            // Apply the effect polymorphically
            spent->UseEffect(pGrid, pState, pPlayer);
            // Delete the consumable -- it has been spent
            delete spent;
            // Do NOT advance i: the next item has shifted into slot i
        }
        else
        {
            i++; // player kept this item; move to the next slot
        }
    }
}

// ============================================================
//  ReadActionParameters
//  Generates the random command pool and lets the player
//  pick their movement commands for this round.
// ============================================================

void SelectCommandsAction::ReadActionParameters()
{
    Grid*      pGrid   = pManager->GetGrid();
    Output*    pOut    = pGrid->GetOutput();
    Input*     pIn     = pGrid->GetInput();
    GameState* pGS     = pManager->GetGameState();
    Player*    pPlayer = pGS->GetCurrentPlayer();

    int health = pPlayer->GetHealth();

    // Generate a fresh random pool
    pGS->GenerateRandomCommands();
    Command* pool     = pGS->GetRandomCommandsPool();
    int      poolSize = MaxAvailableCommands;

    // Number of commands = Min(MaxCommands, health)
    int maxCmds = pPlayer->GetMaxCommands(); // 5 normally, 6 with Extended Memory
    int numCmds = (health < maxCmds) ? health : maxCmds;

    pOut->PrintMessage("Player " + to_string(pPlayer->GetHealth()) +
                       " HP -- choose " + to_string(numCmds) + " commands.");

    // Clear any leftover commands from the previous round
    pPlayer->ClearSavedCommands();

    // Let the player click numCmds commands from the pool
    for (int i = 0; i < numCmds; i++)
    {
        // Redraw the bar each iteration so the player sees filled slots
        pOut->CreateCommandsBar(pPlayer->GetSavedCommands(), i, pool, poolSize);

        int poolIndex = -1;
        while (poolIndex < 0 || poolIndex >= poolSize)
        {
            poolIndex = pIn->GetSelectedCommandIndex();
            if (poolIndex == -1)
                pOut->PrintMessage("Click one of the available commands in the bar.");
        }

        Command selected = pool[poolIndex];
        pPlayer->AddSavedCommand(selected);

        pOut->PrintMessage("Slot " + to_string(i + 1) + ": " +
                           GetCommandName(selected) + " saved.");
    }

    // Show the fully filled command bar
    pOut->CreateCommandsBar(pPlayer->GetSavedCommands(), numCmds, pool, poolSize);
}

// ============================================================
//  Execute
// ============================================================

void SelectCommandsAction::Execute()
{
    Grid*      pGrid   = pManager->GetGrid();
    Output*    pOut    = pGrid->GetOutput();
    GameState* pState  = pManager->GetGameState();
    Player*    pPlayer = pState->GetCurrentPlayer();

    // ── 1. Hacked check: skip this player's entire turn ──────
    if (pPlayer->IsHacked())
    {
        pPlayer->SetHacked(false); // reset for future rounds
        pOut->PrintMessage("Your robot was hacked! Turn skipped. Click to continue...");
        int x, y;
        pGrid->GetInput()->GetPointClicked(x, y);
        pOut->ClearStatusBar();
        pState->AdvanceCurrentPlayer();
        return;
    }

    // ── 2. Offer consumables BEFORE assigning commands ───────
    //  (Toolkit repairs; HackDevice hacks opponent; DoubleLaser skipped here)
    OfferConsumables(pGrid, pState, pPlayer);

    // ── 3. Let the player select their movement commands ─────
    ReadActionParameters();

    pOut->PrintMessage("Commands saved. Click 'Execute Commands' to move your robot.");
}
