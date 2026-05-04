#include "Toolkit.h"
#include "Player.h"
#include "Grid.h"

string Toolkit::GetName() const
{
    return "Toolkit";
}

void Toolkit::UseEffect(Grid* pGrid, GameState* /*pState*/, Player* pPlayer)
{
    // Repair the robot to full health without visiting a Workshop
    pPlayer->SetHealth(10);

    Output* pOut = pGrid->GetOutput();
    pOut->PrintMessage("Toolkit used! Robot fully repaired to 10 health. Click to continue...");

    int x, y;
    pGrid->GetInput()->GetPointClicked(x, y);
    pOut->ClearStatusBar();
}
