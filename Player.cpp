#include "Player.h"

#include "GameObject.h"
#include "GameState.h"

Player::Player(Cell* pCell, int playerNum)
	: playerNum(playerNum), health(10), currDirection(RIGHT), savedCommandCount(0)
{
	this->pCell = pCell;

	// Initialise saved commands to NO_COMMAND
	for (int i = 0; i < MaxSavedCommands; i++)
		savedCommands[i] = NO_COMMAND;
}

// ====== Setters and Getters ======

void  Player::SetCell(Cell* cell)   { pCell = cell; }
Cell* Player::GetCell() const       { return pCell; }

void Player::SetHealth(int h)
{
	if (h > 10) {
		health = 10;
	}
	else if (h < 0) {
		health = 0;
	}
	else {
		health = h;
	}
}
int Player::GetHealth() const       { return health; }

Direction Player::GetDirection() const      { return currDirection; }
void      Player::SetDirection(Direction d) { currDirection = d; }

int Player::GetPlayerNumber() {
	return playerNum;
}
// ====== Saved Commands ======

void Player::AddSavedCommand(Command cmd)
{
	if (savedCommandCount < MaxSavedCommands)
		savedCommands[savedCommandCount++] = cmd;
}

void Player::ClearSavedCommands()
{
	for (int i = 0; i < MaxSavedCommands; i++)
		savedCommands[i] = NO_COMMAND;
	savedCommandCount = 0;
}

int     Player::GetSavedCommandCount() const { return savedCommandCount; }
Command Player::GetSavedCommand(int index) const
{
	if (index >= 0 && index < savedCommandCount)
		return savedCommands[index];
	return NO_COMMAND;
}
Command* Player::GetSavedCommands()
{
	return savedCommands;
}
// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];

	///TODO: Call the appropriate Output function to draw the player token with playerColor
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum,playerColor, currDirection);

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = UI.CellColor;
	if (this->GetCell()->GetWaterPit()) {
		cellColor = UI.WaterPitsCellColor;
	}
	else if (this->GetCell()->GetDangerZone()) {
		cellColor = UI.DangerZoneCellColor;
	}
	//       (hint: may differ from UI.CellColor if cell is a WaterPit or DangerZone)
	pOut->DrawCell(this->GetCell()->GetCellPosition(), cellColor);
	
}

// ====== Game Logic ======

void Player::Move(Grid* pGrid, GameState* pState)
{
	///TODO: Implement this function
	// - Execute the saved commands one by one, waiting for a mouse click between each
	// - After all commands are executed, apply the game object effect at the final cell (if any)
	// - Use CellPosition and Grid to handle movement and cell updates
}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	// TODO: Modify the Info as needed
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(currDirection) + ", ";
	playersInfo += to_string(health) + ")";
}
