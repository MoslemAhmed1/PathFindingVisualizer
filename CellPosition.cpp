#include "CellPosition.h"
#include "UI_Info.h"
#include <iostream>
using namespace std;

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