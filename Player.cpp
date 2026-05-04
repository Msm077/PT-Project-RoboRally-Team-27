#include "Player.h"

#include "Output.h"
#include "Grid.h"
#include "Cell.h"
#include "GameState.h"
#include "Consumable.h"
#include "Workshop.h"
<<<<<<< Updated upstream
#include "WaterPit.h"
#include "DangerZone.h"
#include "Consumable.h"
#include <string>
using namespace std;

// ============================================================
//  Private helper: ExecuteCommand
// ============================================================
=======

//  Constructor / Destructor
// 
>>>>>>> Stashed changes

Player::Player(Cell* pStartCell, int num)
    : playerNum(num),
    health(10),
    currDirection(RIGHT),
    savedCommandCount(0),
    isHacked(false),
    equippedDevice(NO_DEVICE),
    laserDamage(1),
    inventoryCount(0)
{
<<<<<<< Updated upstream
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
=======
    pCell = pStartCell;
    startCell = pCell;

    for (int i = 0; i < MaxSavedCommands; i++)
        savedCommands[i] = NO_COMMAND;

    for (int i = 0; i < MaxConsumables; i++)
        inventory[i] = nullptr;
}

Player::~Player()
{
    // Player owns every Consumable* in inventory; delete any remaining ones.
>>>>>>> Stashed changes
    for (int i = 0; i < inventoryCount; i++)
    {
        delete inventory[i];
        inventory[i] = nullptr;
    }
}

// ============================================================
<<<<<<< Updated upstream
//  Setters / Getters
=======
//  Setters and Getters
>>>>>>> Stashed changes
// ============================================================

void  Player::SetCell(Cell* cell) { pCell = cell; }
Cell* Player::GetCell()     const { return pCell; }

void Player::SetHealth(int h)
{
<<<<<<< Updated upstream
    if (h < 0)  h = 0;
    if (h > 10) h = 10;
    health = h;
}
int  Player::GetHealth() const { return health; }

Direction Player::GetDirection()      const { return currDirection; }
=======
    if (h > 10) health = 10;
    else if (h < 0)  health = 0;
    else             health = h;
}

int Player::GetHealth() const { return health; }

Direction Player::GetDirection()          const { return currDirection; }
>>>>>>> Stashed changes
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

int     Player::GetSavedCommandCount()       const { return savedCommandCount; }
Command Player::GetSavedCommand(int index)   const
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
<<<<<<< Updated upstream
    color cellColor = UI.CellColor;

    if (pCell->HasWaterPit())
        cellColor = UI.WaterPitsCellColor;
    else if (pCell->HasDangerZone())
        cellColor = UI.DangerZoneCellColor;

    pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor, currDirection);
}

// ============================================================
//  Move  (executes saved commands one by one)
=======
    // Redraw the cell background at the player's current position,
    // then redraw whichever game object the cell holds (if any),
    // so neither the cell colour nor any object icon is erased.
    CellPosition pos = pCell->GetCellPosition();
    pOut->DrawCell(pos, UI.CellColor);

    GameObject* pObj = pCell->GetGameObject();
    if (pObj)
        pObj->Draw(pOut);
}

// ============================================================
//  Private helper: execute a single command and update pos
// ============================================================

void Player::ExecuteCommand(Command cmd, CellPosition& pos)
{
    // ── Rotation commands ─────────────────────────────────────────
    if (cmd == ROTATE_CLOCKWISE)
    {
        switch (currDirection)
        {
        case UP:    currDirection = RIGHT; break;
        case RIGHT: currDirection = DOWN;  break;
        case DOWN:  currDirection = LEFT;  break;
        case LEFT:  currDirection = UP;    break;
        }
        return; // rotation does not change position
    }

    if (cmd == ROTATE_COUNTERCLOCKWISE)
    {
        switch (currDirection)
        {
        case UP:    currDirection = LEFT;  break;
        case LEFT:  currDirection = DOWN;  break;
        case DOWN:  currDirection = RIGHT; break;
        case RIGHT: currDirection = UP;    break;
        }
        return;
    }

    // ── Movement commands ─────────────────────────────────────────
    int steps = 0;
    switch (cmd)
    {
    case MOVE_FORWARD_ONE_STEP:     steps = 1; break;
    case MOVE_FORWARD_TWO_STEPS:    steps = 2; break;
    case MOVE_FORWARD_THREE_STEPS:  steps = 3; break;
    case MOVE_BACKWARD_ONE_STEP:    steps = -1; break;
    case MOVE_BACKWARD_TWO_STEPS:   steps = -2; break;
    case MOVE_BACKWARD_THREE_STEPS: steps = -3; break;
    default: return; // NO_COMMAND or unknown
    }

    int targetV = pos.VCell();
    int targetH = pos.HCell();

    // vCell = 0 is the TOP row, so moving UP means decreasing vCell.
    switch (currDirection)
    {
    case UP:    targetV -= steps; break;
    case DOWN:  targetV += steps; break;
    case RIGHT: targetH += steps; break;
    case LEFT:  targetH -= steps; break;
    }

    // Clamp to valid grid bounds: vCell in [0, NumVerticalCells-1],
    //                             hCell in [0, NumHorizontalCells-1]
    if (targetV < 0)                    targetV = 0;
    if (targetV > NumVerticalCells - 1) targetV = NumVerticalCells - 1;
    if (targetH < 0)                    targetH = 0;
    if (targetH > NumHorizontalCells - 1) targetH = NumHorizontalCells - 1;

    pos.SetVCell(targetV);
    pos.SetHCell(targetH);
}

// ============================================================
//  Move  -- executes all saved commands one by one
>>>>>>> Stashed changes
// ============================================================

void Player::Move(Grid* pGrid, GameState* pState)
{
    Output* pOut = pGrid->GetOutput();
    Input*  pIn  = pGrid->GetInput();

<<<<<<< Updated upstream
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
=======
    // Track whether the player ever lands on a Workshop during movement.
    // Per the rules, Workshop effect is applied only after ALL commands finish.
    Workshop* pFinalWorkshop = nullptr;

    for (int i = 0; i < savedCommandCount; i++)
    {
        // Prompt user to click before each command executes.
        pOut->PrintMessage("Click to execute command " + to_string(i + 1) + " of "
            + to_string(savedCommandCount) + "...");
        int x, y;
        pIn->GetPointClicked(x, y);

        // Erase player from current cell.
        ClearDrawing(pOut);

        // Compute new position after this command.
        CellPosition newPos = pCell->GetCellPosition();
        ExecuteCommand(savedCommands[i], newPos);

        // Move the player in the Grid (updates pCell and redraws token).
        pGrid->UpdatePlayerCell(this, newPos);

        // Refresh the whole board so every object and player is visible.
        pGrid->UpdateInterface(pState);

        // Check whether the game ended as a side-effect of UpdateInterface
        // (e.g. WaterPit reset already triggered SetEndGame).
        // We will check after applying the object below.

        // Apply the game object at the new cell -- but NOT Workshop yet.
>>>>>>> Stashed changes
        GameObject* pObj = pCell->GetGameObject();
        if (pObj)
        {
<<<<<<< Updated upstream
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

=======
            // dynamic_cast here is sanctioned: we check only to *defer*
            // the Workshop, not to replace virtual dispatch.
            Workshop* pWS = dynamic_cast<Workshop*>(pObj);
            if (pWS)
            {
                pFinalWorkshop = pWS; // remember for after all commands
            }
            else
            {
                pObj->Apply(pGrid, pState, this);

                // If the object ended the game (Flag, WaterPit death, etc.),
                // stop processing further commands.
                if (pState->GetEndGame())
                    return;
            }
        }
    }

    // After ALL commands: apply the Workshop the player is currently on
    // (the rules state Workshop triggers only once, at the very end).
    GameObject* pLastObj = pCell->GetGameObject();
    Workshop* pLastWS = dynamic_cast<Workshop*>(pLastObj);
    if (pLastWS)
    {
        pLastWS->Apply(pGrid, pState, this);
    }

    // Clear the saved command list for the next round.
>>>>>>> Stashed changes
    ClearSavedCommands();
}

// ============================================================
//  AppendPlayerInfo
<<<<<<< Updated upstream
=======
//  Builds a compact status string, e.g.: "P1(3, Right, 10)"
>>>>>>> Stashed changes
// ============================================================

void Player::AppendPlayerInfo(string& playersInfo) const
{
<<<<<<< Updated upstream
    // Direction strings
    const string dirNames[] = { "Up", "Down", "Right", "Left" };

    playersInfo += "P" + to_string(playerNum + 1) + "(";
    playersInfo += dirNames[currDirection] + ", ";
    playersInfo += to_string(health) + ")";
}

// ============================================================
//  incrementHealth  (used by Reboot & Repair action)
=======
    string dirStr;
    switch (currDirection)
    {
    case UP:    dirStr = "Up";    break;
    case DOWN:  dirStr = "Down";  break;
    case RIGHT: dirStr = "Right"; break;
    case LEFT:  dirStr = "Left";  break;
    }

    playersInfo += "P" + to_string(playerNum + 1)
        + "(" + to_string(pCell->GetCellPosition().GetCellNum())
        + ", " + dirStr
        + ", " + to_string(health)
        + ")";
}

// ============================================================
//  incrementHealth  (Reboot & Repair action)
>>>>>>> Stashed changes
// ============================================================

void Player::incrementHealth()
{
<<<<<<< Updated upstream
    SetHealth(health + 1); // SetHealth clamps to [0,10]
=======
    SetHealth(health + 1); // SetHealth clamps to [0, 10]
>>>>>>> Stashed changes
}

// ============================================================
//  Device (Extended Memory)
// ============================================================

int Player::GetMaxCommands() const
{
<<<<<<< Updated upstream
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

=======
    // Extended Memory grants 6 command slots instead of the default 5.
    return (equippedDevice == EXTENDED_MEMORY) ? 6 : 5;
}

void       Player::SetDevice(DeviceType d) { equippedDevice = d; }
DeviceType Player::GetDevice()       const { return equippedDevice; }

// ============================================================
//  Consumable Inventory
// ============================================================

void Player::AddConsumable(Consumable* pConsumable)
{
    if (inventoryCount < MaxConsumables)
    {
        inventory[inventoryCount++] = pConsumable; // player takes ownership
    }
    // If inventory is full we silently drop it;
    // callers should check GetInventoryCount() before calling.
}

>>>>>>> Stashed changes
Consumable* Player::RemoveConsumable(int index)
{
    if (index < 0 || index >= inventoryCount)
        return nullptr;
<<<<<<< Updated upstream

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
=======

    Consumable* pRemoved = inventory[index];

    // Shift the remaining pointers left to keep the array compact.
    for (int i = index; i < inventoryCount - 1; i++)
        inventory[i] = inventory[i + 1];

    inventory[--inventoryCount] = nullptr;
    return pRemoved; // caller is responsible for deleting
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
void Player::SetLaserDamage(int d) { laserDamage = d; }

bool Player::IsFacingPlayer(const Player* pOpponent) const
{
    CellPosition myPos = pCell->GetCellPosition();
    CellPosition opPos = pOpponent->GetCell()->GetCellPosition();

    int myV = myPos.VCell(), myH = myPos.HCell();
    int opV = opPos.VCell(), opH = opPos.HCell();

    // The opponent must share the same row OR the same column,
    // AND must be directly in front (in the facing direction).
    switch (currDirection)
    {
    case UP:
        // Opponent is in the same column, above this player (smaller vCell).
        return (myH == opH) && (opV < myV);

    case DOWN:
        // Opponent is in the same column, below this player (larger vCell).
        return (myH == opH) && (opV > myV);

    case RIGHT:
        // Opponent is in the same row, to the right (larger hCell).
        return (myV == opV) && (opH > myH);

    case LEFT:
        // Opponent is in the same row, to the left (smaller hCell).
        return (myV == opV) && (opH < myH);
    }

    return false;
}

// ============================================================
//  Hacked flag
// ============================================================

void Player::SetHacked(bool hacked) { isHacked = hacked; }
bool Player::IsHacked()       const { return isHacked; }

void Player::Reset() {
    pCell = startCell;

    // Initialise saved commands to NO_COMMAND
    for (int i = 0; i < MaxSavedCommands; i++)
        savedCommands[i] = NO_COMMAND;
    for (int i = 0; i < MaxConsumables; i++)
        delete inventory;
    health = 10; currDirection = RIGHT; savedCommandCount = 0; equippedDevice = NO_DEVICE; inventoryCount = 0; isHacked = false;
}
>>>>>>> Stashed changes
