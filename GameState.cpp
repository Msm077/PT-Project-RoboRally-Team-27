#include "GameState.h"
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()
#include <random>
#include <iostream>
#include "Grid.h"
#include "Player.h"
#include "Cell.h"
#include "Output.h"

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
	return PlayerList[currPlayerNumber];
}

Player* GameState::GetPlayer(int playerNum) const
{
	///TODO: Return the player with the given player number
	if (playerNum >= 0 && playerNum < MaxPlayerCount)
		return PlayerList[playerNum];
	return nullptr;
}
void GameState::ResetAllPlayers() {
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->Reset(); 
	}
}
// ========== Turn Management ==========

void GameState::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount;
}

void GameState::SetFirstPlayer(int playerNum)
{currPlayerNumber = playerNum;


	///TODO: Implement this function to set which player goes first this round
}
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
	// MOVEMENT --> SHOOTING --> MOVEMENT --> ...
	if (currentPhase == PHASE_MOVEMENT)
		currentPhase = PHASE_SHOOTING;
	else
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

void GameState::EndGame() {

}
// ========== Drawing Helpers ==========

void GameState::DrawAllPlayers(Output* pOut) const
{
	///TODO: Draw all players
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->Draw(pOut);
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
