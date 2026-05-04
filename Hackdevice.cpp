#include "HackDevice.h"
#include "Player.h"
#include "GameState.h"
#include "Grid.h"

string HackDevice::GetName() const
{
    return "Hack Device";
}

void HackDevice::UseEffect(Grid* pGrid, GameState* pState, Player* pPlayer)
{
    // Find the opponent: the player who is NOT pPlayer
    // GameState owns exactly MaxPlayerCount players; find the other one.
    Player* pOpponent = nullptr;
    for (int i = 0; i < MaxPlayerCount; i++)
    {
        Player* p = pState->GetPlayer(i);
        if (p != pPlayer)
        {
            pOpponent = p;
            break;
        }
    }

    if (pOpponent)
    {
        pOpponent->SetHacked(true);
    }

    Output* pOut = pGrid->GetOutput();
    pOut->PrintMessage("Hack Device used! Opponent will skip their next turn. Click to continue...");

    int x, y;
    pGrid->GetInput()->GetPointClicked(x, y);
    pOut->ClearStatusBar();
}
