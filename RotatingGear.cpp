 #include "RotatingGear.h"




RotatingGear::RotatingGear(const CellPosition & gearposition,bool clockwise) : GameObject(gearposition)
{
	isClockWise = clockwise;
}

void RotatingGear::Draw(Output* pOut) const
{
	pOut->DrawRotatingGear(position, isClockWise);
}

void RotatingGear::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message and change the message according to direction of rotation "You have reached a rotating gear, you will rotate (clockwise/ anti-clockwise) Click to continue ..." and wait mouse click
	//2- Apply the roating gear's effect by rotating the player according to the direction
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    // 1. Inform the player what is happening and wait for a click to continue
    string msg = "You have reached a rotating gear, you will rotate ";
    msg += isClockWise ? "clockwise" : "anti-clockwise";
    msg += ". Click to continue...";
    pOut->PrintMessage(msg);

    int x, y;
    pIn->GetPointClicked(x, y);

    // 2. Apply the rotation to the player
    //    Rotating clockwise:         UP->RIGHT->DOWN->LEFT->UP
    //    Rotating counter-clockwise: UP->LEFT->DOWN->RIGHT->UP
    Direction current = pPlayer->GetDirection();
    Direction next;

    if (isClockWise)
    {
        switch (current)
        {
        case UP:    next = RIGHT; break;
        case RIGHT: next = DOWN;  break;
        case DOWN:  next = LEFT;  break;
        case LEFT:  next = UP;    break;
        default:    next = current; break;
        }
    }
    else // counter-clockwise
    {
        switch (current)
        {
        case UP:    next = LEFT;  break;
        case LEFT:  next = DOWN;  break;
        case DOWN:  next = RIGHT; break;
        case RIGHT: next = UP;    break;
        default:    next = current; break;
        }
    }

    pPlayer->SetDirection(next);
    pOut->ClearStatusBar();
}
bool RotatingGear::GetisClockWise() const
{
	return isClockWise;
}

void RotatingGear::Save(ofstream& OutFile, Type t) {
	if (IsObject(t)) {
		OutFile << position.GetCellNum() << " " << this->GetisClockWise() << endl;
	}
	else {
		return;
	}
}

void RotatingGear::Read(ifstream& Infile) {
	int x1;
	bool b1;
	
		Infile >> x1 >> b1;
		position = x1;
		isClockWise = b1;
	
}

bool RotatingGear::IsObject(Type t) {
	if (t == RotatingGears) {
		return 1;
	}
	return 0;
}
GameObject* RotatingGear::Photocopy(const CellPosition& newPos) const
{
	return new RotatingGear(newPos, isClockWise);
}
RotatingGear::~RotatingGear()
{
}
