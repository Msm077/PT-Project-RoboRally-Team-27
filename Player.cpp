#include "Player.h"
#include "Grid.h"
#include "GameObject.h"
#include "GameState.h"
#include "Workshop.h"
#include "SelectCommandsAction.h"
#include "Input.h"
#include<iostream>
#include "WaterPit.h"
#include "DangerZone.h"


using namespace std;

void Player::ExecuteCommand(Command cmd, CellPosition& pos)
{
    int steps = 0;
    bool isRotation = false;

    // 1st knowing the number of steps based on the command
    switch (cmd)
    {
    case MOVE_FORWARD_ONE_STEP:     steps = 1;  break;
    case MOVE_FORWARD_TWO_STEPS:    steps = 2;  break;
    case MOVE_FORWARD_THREE_STEPS:  steps = 3;  break;
    case MOVE_BACKWARD_ONE_STEP:    steps = -1; break;
    case MOVE_BACKWARD_TWO_STEPS:   steps = -2; break;
    case MOVE_BACKWARD_THREE_STEPS: steps = -3; break;
    case ROTATE_CLOCKWISE:
    case ROTATE_COUNTERCLOCKWISE:
        isRotation = true;
        break;
    default: return; // NO_COMMAND
    }

    // 2. adjusting rotation
    if (isRotation)
    {
        // 90 degrees clockwise
        if (cmd == ROTATE_CLOCKWISE) 
        {
            if (currDirection == UP)
            {
                currDirection = RIGHT;
            }
            else if (currDirection == RIGHT)
            {
                currDirection = DOWN;
            }
            else if (currDirection == DOWN) { 
                currDirection = LEFT; }
            else if (currDirection == LEFT) { currDirection = UP; }
        }
        else // 90 degrees counter-clockwise
        {
            if (currDirection == UP) {
                currDirection = LEFT;
            }
            else if (currDirection == LEFT) {
                currDirection = DOWN;
            }
            else if (currDirection == DOWN) {
                currDirection = RIGHT;
            }
            else if (currDirection == RIGHT) { 
                currDirection = UP; 
            }
        }
        return;
    }

    // getting the current direction
    int targetV = pos.VCell();
    int targetH = pos.HCell();

    /// modifying the current direction

    // cuz Cell 1 is bottom-left, UP increases VCell and RIGHT increases HCell
    if (currDirection == UP) {
        targetV += steps;
    }
    else if (currDirection == DOWN) {
        targetV -= steps;
    }
    else if (currDirection == LEFT) {
        targetH -= steps;
    }
    else if (currDirection == RIGHT) {
        targetH += steps;
    }

    // 4th ensuring sticking for the boundaries
    // rows (VCell)  0 to 4
    // Columns (HCell)  0 to 10.
    if (targetV < 0) {
        targetV = 0;
    }
    if (targetV > 4) {
        targetV = 4;
    }
    if (targetH < 0) {
        targetH = 0;
    }
    if (targetH > 10) {
        targetH = 10;
    }

    // Update the position object
    pos.SetVCell(targetV);
    pos.SetHCell(targetH);

}

Player::Player(Cell* pCell, int playerNum)
	: playerNum(playerNum), health(10), currDirection(RIGHT), savedCommandCount(0), 
    equippedDevice(NO_DEVICE), inventoryCount(0), isHacked(false)
{
	this->pCell = pCell;

	// Initialise saved commands to NO_COMMAND
	for (int i = 0; i < MaxSavedCommands; i++)
		savedCommands[i] = NO_COMMAND;
    for (int i = 0; i < MaxConsumables; i++)
        inventory[i] = NO_CONSUMABLE;
}

// ====== Setters and Getters ======

void  Player::SetCell(Cell* cell)   { pCell = cell; }
Cell* Player::GetCell() const       { return pCell; }

void Player::SetHealth(int h)
{
	///TODO: Add validation (e.g. clamp to 0..MaxHealth)
	health = h;
}
int Player::GetHealth() const       { return health; }

Direction Player::GetDirection() const      { return currDirection; }
void      Player::SetDirection(Direction d) { currDirection = d; }

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

	///TODO: Call the appropriate Output function to draw the player token with playerColor
    color playerColor = UI.PlayerColors[playerNum];
    pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor, currDirection);
}

void Player::ClearDrawing(Output* pOut) const
{
	///TODO: Determine the correct background colour for this cell
	//       (hint: may differ from UI.CellColor if cell is a WaterPit or DangerZone)
	color cellColor = UI.CellColor;

	///TODO: Call the appropriate Output function to draw the token using cellColor (erases it)
    // Check if standing on a special cell to use correct background color

    if (pCell->HasWaterPit())
        cellColor = BLUE;
    else if (pCell->HasDangerZone())
        cellColor = RED;

    pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor, currDirection);
}

// ====== Game Logic ======

void Player::Move(Grid* pGrid, GameState* pState)
{
	///TODO: Implement this function
	// - Execute the saved commands one by one, waiting for a mouse click between each
	// - After all commands are executed, apply the game object effect at the final cell (if any)
	// - Use CellPosition and Grid to handle movement and cell updates
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	for (int i = 0; i < savedCommandCount; i ++) {
        // 1. wait untill thje mouse clicked before executing the next command
        pOut->PrintMessage("Click to execute command " + to_string(i + 1) + "...");
        int x, y;
        pIn->GetPointClicked(x, y);

        // 2nd clear current drawing
        ClearDrawing(pOut);

        // 3rd Updating the player position or rotation
        Command cmd = savedCommands[i];
        CellPosition currentPos = pCell->GetCellPosition();

        // calculating the effect of the command
        ExecuteCommand(cmd, currentPos);

        // 4. Update the player's cell pointer in the Grid
        // this ensures the Grid knows where the player is
        pGrid->UpdatePlayerCell(this, currentPos);

        // 5th drawing the player at the new position
        Draw(pOut);

        // 6. Trigger the Apply() of the game object at the NEW cell
        // exception: the workshop is applied only after the final command
        GameObject* pObj = pCell->GetGameObject();
        if (pObj != nullptr)
        {
            // Use dynamic_cast only to check if it's NOT a Workshop (as per rules)
            Workshop* pWS = dynamic_cast<Workshop*>(pObj);
            if (!pWS)
            {
                pObj->Apply(pGrid, pState, this);
            }
        }
    }

    // talk with msm about this

    // 7. apply Workshop effect if the player ended on it
    GameObject* pFinalObj = pCell->GetGameObject();
    Workshop* pFinalWS = dynamic_cast<Workshop*>(pFinalObj);
    if (pFinalWS)
    {
        pFinalWS->Apply(pGrid, pState, this);
    }

    pOut->PrintMessage("movement round finished. ");
    ClearSavedCommands(); // prepare for the next round by clearing the commands
    pState->AdvanceCurrentPlayer();
	}


void Player::AppendPlayerInfo(string& playersInfo) const
{
	// TODO: Modify the Info as needed
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(currDirection) + ", ";
	playersInfo += to_string(health) + ")";
}

void Player::incrementHealth()
{
    health = health + 1;
}

int Player::GetMaxCommands() const
{
    if (equippedDevice == NO_DEVICE) {
        return 5;
    }
    else if (equippedDevice == EXTENDED_MEMORY) {
        return 6;
    }
}

void Player::SetDevice(DeviceType d)
{
    equippedDevice = d;
}

DeviceType Player::GetDevice() const
{
    return equippedDevice;
}

void Player::AddConsumable(ConsumableType c)
{
    if (inventoryCount < MaxConsumables) {
        inventory[inventoryCount] = c;
        inventoryCount++;
    }
}

bool Player::UseConsumable(ConsumableType c)
{
    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i] == c) {
            // Shift array left to remove it
            for (int j = i; j < inventoryCount - 1; j++)
                inventory[j] = inventory[j + 1];
            inventory[--inventoryCount] = NO_CONSUMABLE;
            return true;
        }
    }
    return false; // didn't have it

}

bool Player::HasConsumable(ConsumableType c) const
{
    for (int i = 0; i < inventoryCount; i++)
        if (inventory[i] == c) return true;
    return false;
}

void Player::SetHacked(bool hacked)
{
    isHacked = hacked;

}

bool Player::IsHacked() const
{
    return isHacked;
}
