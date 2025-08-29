#include "Cell.h"
#include "Grid.h"

Cell::Cell(const CellPosition& pos) : position(pos)
{
	// initializes the data members
	state = PATH;
	gCost = hCost = totalCost = 1e9;
	parent = nullptr;
}

Cell::Cell(int v = 0, int h = 0) : position(v, h)
{
	// initializes the data members
	state = PATH;
	gCost = hCost = totalCost = 1e9;
	parent = nullptr;
}

// ======= Setters and Getters Functions ======= 

void Cell::Set_G_Cost(double cost)
{
	gCost = cost;
}

void Cell::Set_H_Cost(double cost)
{
	hCost = cost;
}

void Cell::SetTotalCost(double cost)
{
	totalCost = cost;
}

void Cell::SetParentCell(Cell* parent)
{
	this->parent = parent;
}

void Cell::SetCellState(CellState newState)
{
	state = newState;
}

double Cell::Get_G_Cost() const
{
	return gCost;
}

double Cell::Get_H_Cost() const
{
	return hCost;
}

double Cell::GetTotalCost() const
{
	return totalCost;
}

Cell* Cell::GetParentCell() const
{
	return parent;
}

CellState Cell::GetCellState() const
{
	return state;
}

CellPosition Cell::GetCellPosition() const
{
	return position;
}

// ======= Overloading Operators =======

bool Cell::operator==(const Cell& other) const
{
	return this->position == other.position;
}

bool Cell::operator!=(const Cell& other) const
{
	return !(this->position == other.position);
}

Cell& Cell::operator=(const Cell& other)
{
	this->position = other.position;
	this->state = other.state;
	this->gCost = other.gCost;
	this->hCost = other.hCost;
	this->totalCost = other.totalCost;
	this->parent = other.parent;

	return *this;
}
