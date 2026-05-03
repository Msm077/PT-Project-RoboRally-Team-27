#include "ApplicationManager.h"
#include <ctime>
#include <cstdlib>

int main()
{
	// 1. Seed the random number generator exactly once. 
	// This ensures your Random Commands Pool is unique in every game session.
	srand(static_cast<unsigned int>(time(0)));

	// 2. Create the ApplicationManager.
	// This will trigger the constructor, creating Output, Input, Grid, and GameState.
	ApplicationManager AppManager;

	ActionType ActType;

	// 3. The Main Game Loop
	do
	{
		// a. Read user action (click on toolbar, grid, or status bar)
		ActType = AppManager.GetUserAction();

		// b. Create and execute the action based on the click
		AppManager.ExecuteAction(ActType);

		// c. Update the interface to reflect any changes (player movement, new objects, etc.)
		AppManager.UpdateInterface();

	} while (ActType != EXIT); // Continue until the user clicks the Exit icon

	return 0;
}