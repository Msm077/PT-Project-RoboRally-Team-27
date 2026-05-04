#include "Workshop.h"
#include "ToolKit.h"
#include "HackDevice.h"

Workshop::Workshop(const CellPosition & workshopPosition):GameObject( workshopPosition)
{

}


void Workshop::Draw(Output * pOut) const
{
	pOut->DrawWorkshop(position);
}

void Workshop::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	///TODO: Implement this function
	// Apply the workshop's effect on the player
	// [OPTIONAL BONUS] Consumables can be given to the player here
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pPlayer->SetHealth(10);
	pOut->PrintMessage("workshop effect has been applies, the robot has been repaired");
	int x, y;
	pIn->GetPointClicked(x, y);

	if (pPlayer->GetDevice() == NO_DEVICE) {
		pOut->PrintMessage("workshop: Buy Extended Memory (6 cmds)? Click YES area / NO area");
	}
	// contact with msm about that
	pIn->GetPointClicked(x, y);
	// Define YES zone as left half of screen, NO as right half (adjust to your UI)
	if (x < UI.width / 2) {
		pPlayer->SetDevice(EXTENDED_MEMORY);
		pOut->PrintMessage("Extended Memory equipped!");
	}

	// --- 3. Consumables: offer Toolkit --- (Inventory Index 0)
	if (!pPlayer->HasToolKitConsumable()){
		pOut->PrintMessage("Workshop: Buy Toolkit (repair anywhere)? Click YES / NO");
		Input* pIn = pGrid->GetInput();
		int x, y;
		pIn->GetPointClicked(x, y);
		if (x < UI.width / 2) {
			pPlayer->AddConsumable(new Toolkit(), 0);
			pOut->PrintMessage("Toolkit added to inventory!");
		}
	}

	// --- 4. Consumables: offer Hack Device ---
	if (!pPlayer->HasHackDeviceConsumable()) {
		pOut->PrintMessage("Workshop: Buy Hack Device (skip opponent)? Click YES / NO");
		Input* pIn = pGrid->GetInput();
		int x, y;
		pIn->GetPointClicked(x, y);
		if (x < UI.width / 2) {
			pPlayer->AddConsumable(new HackDevice(), 1);
			pOut->PrintMessage("Hack Device added to inventory!");
		}
	}
}
void Workshop::Save(ofstream& OutFile, Type t) {
	if (IsObject(t)) {
		OutFile << position.GetCellNum() << endl;
	}
	else {
		return;
	}
}

void Workshop::Read(ifstream& Infile) {
	int x1;
	
		Infile >> x1;
		position = x1;
	
	
}
bool Workshop::IsObject(Type t) {
	if (t == WorkShops) {
		return 1;
	}
	return 0;
}

GameObject* Workshop::Photocopy(const CellPosition& newPos) const
{
	return new Workshop(newPos);
}



Workshop::~Workshop()
{
}
