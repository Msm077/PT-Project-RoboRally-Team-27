 #include "DangerZone.h"



DangerZone::DangerZone(const CellPosition & dangerZonePosition): GameObject(dangerZonePosition)
{
}

void DangerZone::Draw(Output * pOut) const
{
	pOut->DrawDangerZone(position);
}

GameObject* DangerZone::Photocopy(const CellPosition& newPos) const
{
	return new DangerZone(newPos);
}

void DangerZone::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
    pGrid->PrintErrorMessage("You have reached a danger zone. Click to continue ...");

    int oldHealth = pPlayer->GetHealth();
    int newHealth = oldHealth - 1;
    pPlayer->SetHealth(newHealth);

    string msg = "Your health decreased from " + to_string(oldHealth) + 
                 " to " + to_string(newHealth) + ". Click to continue...";
    pGrid->PrintErrorMessage(msg);

    if (newHealth <= 0)
    {
        int playerNum = pPlayer->GetPlayerNumber();
        int winnerNum;
if (playerNum == 0)
{
    winnerNum = 1;
}
else
{
    winnerNum = 0;
}
        pGrid->PrintErrorMessage("Player " + to_string(playerNum) + " has died! Player " + 
                                  to_string(winnerNum) + " wins! Click to continue...");
       // pState->EndG(winnerNum);
    }


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a danger zone. Click to continue ..." and wait mouse click

	// 2- Apply the danger zone's effect by reducing the health of the player by 1 
	// 3- Update the players info which is displayed (check Grid class and decide which function to use)
	
}

void DangerZone::Save(ofstream& OutFile, Type t) {
	if (IsObject(t)) {
		OutFile << position.GetCellNum() << endl;
	}
	else {
		return;
	}
}
void DangerZone::Read(ifstream& Infile) {
	int x1;
		Infile >> x1;
		position = x1;
	
}
bool DangerZone::IsObject(Type t) {
	if (t == DangerZones) {
		return 1;
	}
	return 0;
}
DangerZone::~DangerZone()
{
}
