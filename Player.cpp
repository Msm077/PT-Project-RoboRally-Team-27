#include "Player.h"
#include "Grid.h"
#include "GameObject.h"
#include "GameState.h"
#include "Workshop.h"
#include "WaterPit.h"
#include "DangerZone.h"
#include "Consumable.h"
#include <string>
using namespace std;

// ============================================================
//  Private helper: ExecuteCommand
// ============================================================

void Player::ExecuteCommand(Command cmd, CellPosition& pos)
{
    int  steps     = 0;
    bool isRotation = false;

    switch (cmd)
    {
    case MOVE_FORWARD_ONE_STEP:     steps =  1; break;
    case MOVE_FORWARD_TWO_STEPS:    steps =  2; break;
    case MOVE_FORWARD_THREE_STEPS:  steps =  3; break;
    case MOVE_BACKWARD_ONE_STEP:    steps = -1; break;
    case MOVE_BACKWARD_TWO_STEPS:   steps = -2; break;
    case MOVE_BACKWARD_THREE_STEPS: steps = -3; break;
    case ROTATE_CLOCKWISE:
    case ROTATE_COUNTERCLOCKWISE:
        isRotation = true;
        break;
    default: return; // NO_COMMAND
    }

    if (isRotation)
    {
        if (cmd == ROTATE_CLOCKWISE)
        {
            switch (currDirection)
            {
            case UP:    currDirection = RIGHT; break;
            case RIGHT: currDirection = DOWN;  break;
            case DOWN:  currDirection = LEFT;  break;
            case LEFT:  currDirection = UP;    break;
            }
        }
        else // ROTATE_COUNTERCLOCKWISE
        {
            switch (currDirection)
            {
            case UP:    currDirection = LEFT;  break;
            case LEFT:  currDirection = DOWN;  break;
            case DOWN:  currDirection = RIGHT; break;
            case RIGHT: currDirection = UP;    break;
            }
        }
        return;
    }

    // Movement: adjust vCell / hCell based on direction and step count
    int targetV = pos.VCell();
    int targetH = pos.HCell();

    // VCell increases going UP (row 4 = bottom, row 0 = top)
    switch (currDirection)
    {
    case UP:    targetV += steps; break;
    case DOWN:  targetV -= steps; break;
    case RIGHT: targetH += steps; break;
    case LEFT:  targetH -= steps; break;
    }

    // Clamp to grid boundaries
    if (targetV < 0)  targetV = 0;
    if (targetV > NumVerticalCells   - 1) targetV = NumVerticalCells   - 1;
    if (targetH < 0)  targetH = 0;
    if (targetH > NumHorizontalCells - 1) targetH = NumHorizontalCells - 1;

    pos.SetVCell(targetV);
    pos.SetHCell(targetH);
}

// ============================================================
//  Constructor / Destructor
// ============================================================

Player::Player(Cell* pCell, int playerNum)
    : playerNum(playerNum),
      health(10),
      currDirection(RIGHT),
      savedCommandCount(0),
      isHacked(false),
      equippedDevice(NO_DEVICE),
      laserDamage(1),
      inventoryCount(0)
{
    this->pCell = pCell;

    for (int i = 0; i < MaxSavedCommands; i++)
        savedCommands[i] = NO_COMMAND;

    for (int i = 0; i < MaxConsumables; i++)
        inventory[i] = nullptr;
}

Player::~Player()
{
    // Delete any consumables the player never spent
    for (int i = 0; i < inventoryCount; i++)
    {
        delete inventory[i];
        inventory[i] = nullptr;
    }
}

// ============================================================
//  Setters / Getters
// ============================================================

void  Player::SetCell(Cell* cell) { pCell = cell; }
Cell* Player::GetCell()     const { return pCell; }

void Player::SetHealth(int h)
{
    if (h < 0)  h = 0;
    if (h > 10) h = 10;
    health = h;
}
int  Player::GetHealth() const { return health; }

Direction Player::GetDirection()      const { return currDirection; }
void      Player::SetDirection(Direction d) { currDirection = d; }

// ============================================================
//  Saved Commands
// ============================================================

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
Command* Player::GetSavedCommands() { return savedCommands; }

// ============================================================
//  Drawing
// ============================================================

void Player::Draw(Output* pOut) const
{
    color playerColor = UI.PlayerColors[playerNum];
    pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor, currDirection);
}

void Player::ClearDrawing(Output* pOut) const
{
    color cellColor = UI.CellColor;

    if (pCell->HasWaterPit())
        cellColor = UI.WaterPitsCellColor;
    else if (pCell->HasDangerZone())
        cellColor = UI.DangerZoneCellColor;

    pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor, currDirection);
}

// ============================================================
//  Move  (executes saved commands one by one)
// ============================================================

void Player::Move(Grid* pGrid, GameState* pState)
{
    Output* pOut = pGrid->GetOutput();
    Input*  pIn  = pGrid->GetInput();

    for (int i = 0; i < savedCommandCount; i++)
    {
        pOut->PrintMessage("Click to execute command " + to_string(i + 1) + "...");
        int x, y;
        pIn->GetPointClicked(x, y);

        // Erase current drawing
        ClearDrawing(pOut);

        // Compute new position
        CellPosition currentPos = pCell->GetCellPosition();
        ExecuteCommand(savedCommands[i], currentPos);

        // Move the player on the grid
        pGrid->UpdatePlayerCell(this, currentPos);

        // Redraw at new position
        Draw(pOut);

        // Apply game object at new cell -- except Workshop (deferred to after all commands)
        GameObject* pObj = pCell->GetGameObject();
        if (pObj)
        {
            Workshop* pWS = dynamic_cast<Workshop*>(pObj);
            if (!pWS)
                pObj->Apply(pGrid, pState, this);
        }
    }

    // Apply Workshop effect if the player's final cell has one
    GameObject* pFinalObj = pCell->GetGameObject();
    if (pFinalObj)
    {
        Workshop* pFinalWS = dynamic_cast<Workshop*>(pFinalObj);
        if (pFinalWS)
            pFinalWS->Apply(pGrid, pState, this);
    }

    pOut->PrintMessage("Movement phase finished. Click to continue...");
    int x, y;
    pIn->GetPointClicked(x, y);
    pOut->ClearStatusBar();

    ClearSavedCommands();
}

// ============================================================
//  AppendPlayerInfo
// ============================================================

void Player::AppendPlayerInfo(string& playersInfo) const
{
    // Direction strings
    const string dirNames[] = { "Up", "Down", "Right", "Left" };

    playersInfo += "P" + to_string(playerNum + 1) + "(";
    playersInfo += dirNames[currDirection] + ", ";
    playersInfo += to_string(health) + ")";
}

// ============================================================
//  incrementHealth  (used by Reboot & Repair action)
// ============================================================

void Player::incrementHealth()
{
    SetHealth(health + 1); // SetHealth clamps to [0,10]
}

// ============================================================
//  Device (Extended Memory)
// ============================================================

int Player::GetMaxCommands() const
{
    return (equippedDevice == EXTENDED_MEMORY) ? 6 : 5;
}

void       Player::SetDevice(DeviceType d) { equippedDevice = d; }
DeviceType Player::GetDevice()       const { return equippedDevice; }

// ============================================================
//  Consumable Inventory
// ============================================================

void Player::AddConsumable(Consumable* pConsumable)
{
    // Ignore if inventory is full or pointer is null
    if (!pConsumable || inventoryCount >= MaxConsumables)
        return;

    inventory[inventoryCount++] = pConsumable;
}

Consumable* Player::RemoveConsumable(int index)
{
    if (index < 0 || index >= inventoryCount)
        return nullptr;

    Consumable* removed = inventory[index];

    // Shift remaining items left
    for (int i = index; i < inventoryCount - 1; i++)
        inventory[i] = inventory[i + 1];

    inventory[--inventoryCount] = nullptr;
    return removed; // Caller now owns the pointer and must delete it after use
}

bool Player::HasConsumableNamed(const string& name) const
{
    return FindConsumable(name) != -1;
}

int Player::FindConsumable(const string& name) const
{
    for (int i = 0; i < inventoryCount; i++)
        if (inventory[i] && inventory[i]->GetName() == name)
            return i;
    return -1;
}

int         Player::GetInventoryCount()       const { return inventoryCount; }
Consumable* Player::GetConsumable(int index)  const
{
    if (index >= 0 && index < inventoryCount)
        return inventory[index];
    return nullptr;
}

// ============================================================
//  Laser / Shooting Phase
// ============================================================

int  Player::GetLaserDamage()      const { return laserDamage; }
void Player::SetLaserDamage(int d)       { laserDamage = d; }

bool Player::IsFacingPlayer(const Player* pOpponent) const
{
    if (!pOpponent) return false;

    CellPosition myPos  = pCell->GetCellPosition();
    CellPosition oppPos = pOpponent->GetCell()->GetCellPosition();

    // Must be in the same row or same column to be able to hit
    switch (currDirection)
    {
    case RIGHT:
        // Same row, opponent is to the right
        return (myPos.VCell() == oppPos.VCell()) && (oppPos.HCell() > myPos.HCell());

    case LEFT:
        // Same row, opponent is to the left
        return (myPos.VCell() == oppPos.VCell()) && (oppPos.HCell() < myPos.HCell());

    case UP:
        // VCell increases going up; opponent has a higher VCell
        return (myPos.HCell() == oppPos.HCell()) && (oppPos.VCell() > myPos.VCell());

    case DOWN:
        // Opponent has a lower VCell
        return (myPos.HCell() == oppPos.HCell()) && (oppPos.VCell() < myPos.VCell());
    }
    return false;
}

// ============================================================
//  Hacked flag
// ============================================================

void Player::SetHacked(bool hacked) { isHacked = hacked; }
bool Player::IsHacked()       const { return isHacked; }
