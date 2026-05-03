#include "ReadGridAction.h"



ReadGridAction::ReadGridAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}


void ReadGridAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	
	
	pOut->PrintMessage("Write the name of the file to load");
	saveName = pIn->GetSrting(pOut);
	inFile.open("Saves\\" + saveName + ".txt");
	pOut->ClearStatusBar();
}

void ReadGridAction::Execute()
{
	ReadActionParameters();
	
	Grid* pGrid = pManager->GetGrid();

	pGrid->ClearGrid();
	int n; GameObject* pObj;
	inFile >> n;
	
	for (int i = 0; i < n; i++) {
		pObj = new Flag(NULL);
		pObj->Read(inFile);
		pGrid->AddObjectToCell(pObj);
		
	}
	inFile >> n;
	for (int i = 0; i < n; i++) {
		pObj = new WaterPit(NULL);
		pObj->Read(inFile);
		pGrid->AddObjectToCell(pObj);
		
	}
	inFile >> n;
	for (int i = 0; i < n; i++) {
		pObj = new DangerZone(NULL);
		pObj->Read(inFile);
		pGrid->AddObjectToCell(pObj);
		
	}
	inFile >> n;
	for (int i = 0; i < n; i++) {
		pObj = new Belt(NULL,NULL);
		pObj->Read(inFile);
		pGrid->AddObjectToCell(pObj);
		
	}
	inFile >> n;
	for (int i = 0; i < n; i++) {
		pObj = new Workshop(NULL);
		pObj->Read(inFile);
		pGrid->AddObjectToCell(pObj);
		
	}
	inFile >> n;
	for (int i = 0; i < n; i++) {
		pObj = new Antenna(NULL);
		pObj->Read(inFile);
		pGrid->AddObjectToCell(pObj);
		
	}
	inFile >> n;
	for (int i = 0; i < n; i++) {
		pObj = new RotatingGear(NULL, 0);
		pObj->Read(inFile);
		pGrid->AddObjectToCell(pObj);
		
	}
	inFile.close();
	

}

ReadGridAction::~ReadGridAction()
{
}
