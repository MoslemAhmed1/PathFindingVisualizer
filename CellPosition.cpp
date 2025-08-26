#include "CellPosition.h"
#include "UI_Info.h"
#include <iostream>
using namespace std;

bool CellPosition::operator==(const CellPosition& other) const 
{ 
	return ((this->hCell == other.hCell) && (this->vCell == other.vCell)); 
}

CellPosition& CellPosition::operator=(const CellPosition& other) 
{
	if (this == &other) 
		return *this; // prevent self-assignment

	this->hCell = other.hCell;
	this->vCell = other.vCell;

	return *this;
}

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

bool CellPosition::SetVCell(int v)
{

	if (v >= 0 && v < NumVerticalCells)
	{
		vCell = v;
		return true;
	}

	return false;
}

bool CellPosition::SetHCell(int h)
{

	if (h >= 0 && h < NumHorizontalCells)
	{
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

	if ((VCell() >= 0 && VCell() < NumVerticalCells) && (HCell() >= 0 && HCell() < NumHorizontalCells))
	{
		return true;
	}

	return false;
}





/*
int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file

	// Validation
	if (cellPosition.VCell() == -1 || cellPosition.HCell() == -1) return -1;

	int cellNum = 0;
	cellNum = ((8 - cellPosition.VCell()) * 11) + (cellPosition.HCell() + 1);

	return cellNum; // this line should be changed with your implementation

}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file

	if (cellNum < 1 || cellNum > 99)
	{
		position.SetHCell(-1);
		position.SetVCell(-1);
		return position;
	}

	int hCell = (cellNum - 1) % 11;
	int vCell = 8 - ((cellNum - hCell - 1) / 11);

	position.SetHCell(hCell);
	position.SetVCell(vCell);

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum(int addedNum)
{

	/// TODO: Implement this function as described in the .h file

	*this = GetCellPositionFromNum(GetCellNum() + addedNum);

	// Note: this function updates the data members (vCell and hCell) of the calling object

}
*/