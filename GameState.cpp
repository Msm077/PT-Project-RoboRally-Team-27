#include "GameState.h"

#include "Grid.h"
#include "Player.h"
#include "Cell.h"
#include "Output.h"
#include <iostream>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()


GameState::GameState(Grid* pGrid)
{
	// Create all Player objects starting at the board's designated start cell.
	// The Grid provides the start cell position; the GameState owns the Player objects.
	Cell* startCell = pGrid->GetStartCell();
	Output* pOut = pGrid->GetOutput();

	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(startCell, i);
		PlayerList[i]->Draw(pOut); // draw initial position
	}

	currPlayerNumber = 0;         // Player 0 goes first by default
	currentPhase = PHASE_MOVEMENT;
	endGame = false;
}

GameState::~GameState()
{
	for (int i = 0; i < MaxPlayerCount; i++)
		delete PlayerList[i];
}

// ========== Player Access ==========

Player* GameState::GetCurrentPlayer() const
{
	///TODO: Return the player whose turn it is
	return PlayerList[0]; // wrong -- update this
}

Player* GameState::GetPlayer(int playerNum) const
{
	///TODO: Return the player with the given player number
	return PlayerList[0]; // wrong -- update this
}

// ========== Turn Management ==========

void GameState::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount;
}

void GameState::SetPlayerOrder(int sortedOrder[], int count)
{
	///TODO: Implement this function to set which player goes first this round
}

// ========== Phase Management ==========

PhaseType GameState::GetCurrentPhase() const
{
	return currentPhase;
}

void GameState::SetCurrentPhase(PhaseType phase)
{
	currentPhase = phase;
}

void GameState::AdvancePhase()
{
	// Currently only PHASE_MOVEMENT exists.
	// [OPTIONAL BONUS] If you add PHASE_SHOOTING to the PhaseType enum (DEFS.h),
	// update this to cycle:  MOVEMENT --> SHOOTING --> MOVEMENT
	currentPhase = PHASE_MOVEMENT;
}

// ========== End-Game ==========

bool GameState::GetEndGame() const
{
	return endGame;
}

void GameState::SetEndGame(bool end)
{
	endGame = end;
}

// ========== Drawing Helpers ==========

void GameState::DrawAllPlayers(Output* pOut) const
{
	///TODO: Draw all players
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		pOut->DrawPlayer(PlayerList[i]->GetCell()->GetCellPosition(), PlayerList[i]->GetPlayerNumber(), UI.PlayerColors[PlayerList[i]->GetPlayerNumber()], PlayerList[i]->GetDirection());
	}
}

void GameState::AppendPlayersInfo(string& info) const
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->AppendPlayerInfo(info);
		if (i < MaxPlayerCount - 1)
			info += ", ";
	}
	info += " | Curr = " + to_string(currPlayerNumber);
}
/*
void GameState::GenerateRandomCommands()
{
	for (int i =0; i < MaxAvailableCommands; i++){
	// Get a different random number each time the program runs
	srand(time(0));

	// Generate a random number 
	
	//int randomNum = rand() % (COMMANDS_COUNT - 1) + 1; // Adding 1 shifts the range to [1, COMMANDS_COUNT - 1]. 
	int randomNum =  rand() % 9;
	cout << "i'm in the generate randm commands" << endl;
	cout << randomNum << endl;
	//This effectively skips NO_COMMAND (which is index 0) so the pool only contains useful actions.

	// adding the command to the array after maping it according to the enum of command
	availableRandomPool[i] = static_cast<Command> (randomNum);


	}
}
*/
#include <random>

void GameState::GenerateRandomCommands()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, COMMANDS_COUNT - 1);

	for (int i = 0; i < MaxAvailableCommands; i++) {
		int randomNum = dist(gen);
		availableRandomPool[i] = static_cast<Command>(randomNum);
	}
}


Command* GameState::GetRandomCommandsPool()
{
	return availableRandomPool;
}
