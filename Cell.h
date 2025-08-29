#pragma once 

#include "DEFS.h"

// Class forward declarations (their #include is in the .cpp file)
class Grid;

class Cell
{
	CellPosition position;			// the cell position (vCell and hCell) --> will not change after the Cell is constructed
	CellState state;				// Cell State : PATH | WALL | START | END } VISITED | PENDING | FINAL_PATH
	double gCost, hCost, totalCost;	// gCost/totalCost for dijkstra, all 3 for AStar
	Cell* parent;					// parent cell to construct the path

public:

	Cell(const CellPosition& pos);
	Cell(int v, int h);

	// ======= Setters and Getters Functions ======= //

	void Set_G_Cost(double cost);
	void Set_H_Cost(double cost);
	void SetTotalCost(double cost);
	void SetParentCell(Cell* parent);
	void SetCellState(CellState newState);

	double Get_G_Cost() const;
	double Get_H_Cost() const;
	double GetTotalCost() const;
	Cell* GetParentCell() const;
	CellState GetCellState() const;
	CellPosition GetCellPosition() const;

	// ======= Operator Overloading ======= //

	bool operator == (const Cell& other) const;

	bool operator != (const Cell& other) const;

	Cell& operator=(const Cell& other);


};

// Comparator for min-heap(priority queue) based on Cell totalCost
struct CellComparator
{
	bool operator()(const Cell* lhs, const Cell* rhs) const
	{
		return lhs->GetTotalCost() > rhs->GetTotalCost(); // Min-heap: smaller totalCost has higher priority
	}
};