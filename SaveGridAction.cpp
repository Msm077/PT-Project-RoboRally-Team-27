#include "SaveGridAction.h"



SaveGridAction::SaveGridAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void SaveGridAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	

	pOut->PrintMessage("Choose a name for the save file");
	saveName = pIn->GetSrting(pOut);
	outputFile.open("Saves\\"+saveName+".txt");
	pOut->ClearStatusBar();
}

void SaveGridAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();


	ReadActionParameters();
	outputFile << pGrid->GetNumberofObject(Flags) << endl;
	pGrid->SaveAll(outputFile, Flags);
	outputFile << pGrid->GetNumberofObject(WaterPits) << endl;
	pGrid->SaveAll(outputFile, WaterPits);
	outputFile << pGrid->GetNumberofObject(DangerZones) << endl;
	pGrid->SaveAll(outputFile, DangerZones);
	outputFile << pGrid->GetNumberofObject(Belts) << endl;
	pGrid->SaveAll(outputFile, Belts);
	outputFile << pGrid->GetNumberofObject(WorkShops) << endl;
	pGrid->SaveAll(outputFile, WorkShops);
	outputFile << pGrid->GetNumberofObject(Antennas) << endl;
	pGrid->SaveAll(outputFile, Antennas);
	outputFile << pGrid->GetNumberofObject(RotatingGears) << endl;
	pGrid->SaveAll(outputFile, RotatingGears);
	outputFile.close();

}

SaveGridAction::~SaveGridAction()
{
}
