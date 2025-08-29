#pragma once 

#include "UI_Info.h"
#include "DEFS.h"
#include "CellPosition.h"

// Class forward declarations (their #include is in the .cpp file)
class Grid;
class Output;

class Cell
{
	CellPosition position;	// the cell position (vCell and hCell) --> will not change after the Cell is constructed
	CellState state;				// Cell State : PATH | WALL | VISITED | PENDING | FINAL_PATH
	double gCost, hCost, totalCost;		// gCost for dijkstra, all 3 fro AStar
	Cell* parent;					// parent cell to construct the path

public:

	Cell(const CellPosition& pos); // A constructor initializes the cell position with the passed CellPosition
	Cell(int v, int h);		        // A constructor initializes the cell position with the passed vCell and hCell

	// ======= Setters and Getters Functions ======= //

	void Set_G_Cost(double cost);
	void Set_H_Cost(double cost);
	void SetTotalCost(double cost);
	void SetParentCell(Cell* parent);
	void SetCellState(CellState newState);

	CellPosition GetCellPosition() const;   // A getter for the "position" data member
	CellState GetCellState() const;
	double Get_G_Cost() const;
	double Get_H_Cost() const;
	double GetTotalCost() const;
	Cell* GetParentCell() const;

	// ======= Drawing Functions ======= //

	void DrawCell(Output* pOut) const;	// Draws the Cell

	// ======= Operator Overloading ======= //

	bool operator == (const Cell& other) const;

	bool operator != (const Cell& other) const;

	// bool operator<(const Cell& other) const;

	Cell& operator=(const Cell& other);


};

// Comparator for min-heap based on Cell totalCost
struct CellComparator
{
	bool operator()(const Cell* lhs, const Cell* rhs) const
	{
		return lhs->GetTotalCost() > rhs->GetTotalCost(); // Min-heap: smaller totalCost has higher priority
	}
};

struct CellHash 
{
	std::size_t operator()(const Cell* cell) const 
	{
		// Hash based on cell coordinates
		return std::hash<int>()(cell->GetCellPosition().VCell() * 1000 + cell->GetCellPosition().HCell());
	}
};

struct CellEqual 
{
	bool operator()(const Cell* a, const Cell* b) const 
	{
		// Equality based on cell coordinates
		return a->GetCellPosition().VCell() == b->GetCellPosition().VCell() &&
			a->GetCellPosition().HCell() == b->GetCellPosition().HCell();
	}
};