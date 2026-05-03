#include "ApplicationManager.h"
#include "RebotAndRepairAction.h"

#include "Grid.h"
#include "ExecuteCommandsAction.h"
#include "CopyAction.h"
#include "CutAction.h"
#include "PasteAction.h"
#include "DeleteAction.h"
#include "AddBeltAction.h"
#include "AddRotatingGearAction.h"
#include "AddFlagAction.h"
#include "SwitchToPlayModeAction.h"
#include "SwitchToDesignModeAction.h"
#include "SaveGridAction.h"
#include "ReadGridAction.h"
#include "NewGameAction.h"
///TODO: Add #include for all action types
#include "SelectCommandsAction.h"
#include "ExecuteCommandsAction.h"
#include "SwitchToPlayModeAction.h"
#include "SwitchToDesignModeAction.h"

#include "GameState.h"

ApplicationManager::ApplicationManager()
{
	// Creation order matters:
	//   1. Output / Input  (needed by Grid)
	//   2. Grid            (needed by GameState -- provides the start Cell)
	//   3. GameState       (creates and draws initial players)
	pOut = new Output();
	pIn  = pOut->CreateInput();
	pGrid      = new Grid(pIn, pOut);
	pGameState = new GameState(pGrid);
}

ApplicationManager::~ApplicationManager()
{
	// Deletion order is the reverse of creation:
	//   GameState owns the Players -- delete it first.
	//   Grid owns pIn and pOut     -- delete it last.
	delete pGameState;
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid* ApplicationManager::GetGrid() const
{
	return pGrid;
}

GameState* ApplicationManager::GetGameState() const
{
	return pGameState;
}

void ApplicationManager::UpdateInterface() const
{
	// Grid draws the board; GameState provides player data for drawing.
	pGrid->UpdateInterface(pGameState);
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
		// ========================== Design Mode Actions ==========================

	case SET_BELT:
		pAct = new AddBeltAction(this);
		break;

	case SET_ROTATING_GEAR:
		pAct = new AddRotatingGearAction(this);
		break;

	case SET_FLAG_CELL:
		pAct = new AddFlagAction(this);
		break;

	case TO_PLAY_MODE:
		pAct = new SwitchToPlayModeAction(this);
		break;

		// ========================== Play Mode Actions ==========================

	case SELECT_COMMAND:
		// This triggers the logic you wrote to generate the random pool 
		// and let the player pick their 5 commands.
		pAct = new SelectCommandsAction(this);
		break;

	case EXECUTE_COMMANDS:
		// This triggers the ExecuteCommandsAction which calls Player::Move()
		// and processes the movement logic you implemented.
		pAct = new ExecuteCommandsAction(this);
		break;

	case REBOOT:
		pAct = new RebotAndRepairAction(this);
		break;

	case TO_DESIGN_MODE:
		pAct = new SwitchToDesignModeAction(this);
		break;

		// ========================== Common Actions ==========================

	case EXIT:
		// You might want to create an ExitAction or handle cleanup here
		break;

	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute(); // Execute the action logic (ReadParameters then logic)
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}

/* I COMMENTED FOR TESTING
// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case SET_BELT:
		pAct = new AddBeltAction(this);
		break;

	case SET_ROTATING_GEAR:
		pAct = new AddRotatingGearAction(this);
		break;

	case SET_FLAG_CELL:
		pAct = new AddFlagAction(this);
		break;
	case SAVE:
		pAct = new SaveGridAction(this);
		break;
	case LOAD:
		pAct = new ReadGridAction(this);
		break;

	case TO_PLAY_MODE:
		pAct = new SwitchToPlayModeAction(this);
		break;

	case EXIT:
		break;
	case COPY:
		pAct = new CopyAction(this);
		break;

	case CUT:
		pAct = new CutAction(this);
		break;

	case PASTE:
		pAct = new PasteAction(this);
		break;

	case DELETE_:
		pAct = new DeleteAction(this);
		break;

	///TODO: Add a case for EACH remaining Design Mode action type

	case TO_DESIGN_MODE:
		pAct = new SwitchToDesignModeAction(this);
		break;
	case NEW_GAME:
		pAct = new NewGameAction(this);
		break;
	///TODO: Add a case for EACH remaining Play Mode action type
	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
*/
