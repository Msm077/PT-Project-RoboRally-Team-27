#include "DoubleLaser.h"
#include "Player.h"
#include "Grid.h"

string DoubleLaser::GetName() const
{
    return "Double Laser";
}

void DoubleLaser::UseEffect(Grid* pGrid, GameState* /*pState*/, Player* pPlayer)
{
    // Upgrade this player's laser to deal 2 damage per shot
    pPlayer->SetLaserDamage(2);

    Output* pOut = pGrid->GetOutput();
    pOut->PrintMessage("Double Laser activated! Your laser now deals 2 damage. Click to continue...");

    int x, y;
    pGrid->GetInput()->GetPointClicked(x, y);
    pOut->ClearStatusBar();
}
