#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v) 
{
	if (v >= 0 && v < NumVerticalCells) {

		vCell = v;
		return true;
	}
	return false; // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h) 
{
	if (h >= 0 && h < NumHorizontalCells) {

		hCell = h;
		return true;
	}
	return false;
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	if (vCell >= 0 && vCell < NumVerticalCells && hCell >= 0 && hCell < NumHorizontalCells) {
		return true;
	}

	return false; // this line sould be changed with your implementation
}


int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	if (!cellPosition.IsValidCell()) {
		return -1; // check the validity 
	}
	int v = cellPosition.VCell();  // use getter
	int h = cellPosition.HCell();  // use getter
	return (NumVerticalCells - 1 - v) * NumHorizontalCells + h + 1;  
	/* Key idea: - Grid is stored top → bottom (vCell = 0 at top)
	- BUT numbering is bottom → top (cellNum starts from bottom row)
 So we:
	1) Flip the row index:
	   row_from_bottom = NumVerticalCells - 1 - vCell
	2) Treat grid like a 1D array:
	   index = row_from_bottom * NumHorizontalCells + hCell
	3) Convert to 1-based numbering:
	   cellNum = index + 1
	Final formula:
	   cellNum = (NumVerticalCells - 1 - vCell) * NumHorizontalCells + hCell + 1*/

}
	

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;
	if (cellNum < 1 || cellNum > NumVerticalCells * NumHorizontalCells) {
		
		position.SetVCell(- 1);
		position.SetHCell(-1);
	}
	else {
		int starterfromzero = cellNum-1;
		int h = starterfromzero % NumHorizontalCells;
		position.SetHCell(h);
		int invertedrow = starterfromzero / NumHorizontalCells;
		int v = NumVerticalCells - 1 - invertedrow;
		position.SetVCell(v);
	}/// TODO: Implement this function as described in the .h file

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum(int addedNum, Direction direction)
{
	int initialCellNum = GetCellNum();

	int finalCellNum = initialCellNum;

	switch (direction)
	{
	case UP:
		finalCellNum += addedNum * NumHorizontalCells;
		break;

	case DOWN:
		finalCellNum -= addedNum * NumHorizontalCells;
		break;

	case RIGHT:
		finalCellNum += addedNum;
		break;

	case LEFT:
		finalCellNum -= addedNum;
		break;

	}
	if (finalCellNum < 1 || finalCellNum > NumVerticalCells * NumHorizontalCells) {
		return;
	}
	CellPosition Positionholder = GetCellPositionFromNum(finalCellNum); // ED Added a position holder because the static  function can't use this->


	vCell = Positionholder.VCell();
	hCell = Positionholder.HCell();

	/// TODO: Implement this function as described in the .h file


	// Note: this function updates the data members (vCell and hCell) of the calling object

}