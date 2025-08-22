#pragma once

class CellPosition
{
	int vCell; // the vertical cell number: starts from 0 to NumVerticalCells - 1
	int hCell; // the horizontal cell number: starts from 0 to NumHorizontalCells - 1

public:
	CellPosition(); // Initializes the cell to (-1,-1) indicating not initialized with valid values
	CellPosition(int v, int h); // Sets vCell and hCell if valid
//	CellPosition(int cellNum);  // Sets vCell and hCell from the passed cellNum if valid

	// Note: this class does NOT deal with real coordinates, it deals with the "vCell", "hCell" and "cellNum" instead

	// assuming NumVerticalCells = 19 and NumHorizontalCells = 10
	
	bool SetVCell(int v); // The setter of vCell (the setter here sets only if "v" is in grid range)

	bool SetHCell(int h); // The setter of hCell (the setter here sets only if the "h" is in grid range)

	int VCell() const; // The getter of vCell
	int HCell() const; // The getter of hCell

	bool IsValidCell() const; // Checks if the current cell position (vCell and hCell) both are valid

//	int GetCellNum() const;   // Gets the cellNum from the vCell and hCell of the cell position

//	static int GetCellNumFromPosition(const CellPosition& cellPosition);  // Calculates the cellNum of the passed "cellPosition"
	// It is a static function (no need for a calling obj)

//	static CellPosition GetCellPositionFromNum(int cellNum); // Returns the corresponding CellPosition (vCell, hCell) of the passed cellNum
	// It is a static function (no need for a calling obj)


//	void AddCellNum(int addedNum); // Adds the passed "addedNum" to the "cellNum" of the current cell position
	// and updates the data members (vCell and hCell) accordingly

	bool operator == (const CellPosition& other) const;

	CellPosition& operator=(const CellPosition& other);

};
