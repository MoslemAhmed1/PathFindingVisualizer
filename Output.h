#pragma once

#include "DEFS.h"
#include "UI_Info.h" 
#include "CellPosition.h"
#include "Button.h"
#include <vector>
#include <string>
using namespace std;

// forward declarations (their includes are in the cpp)
class Input;

class Output	// The application manager & grid should have a pointer to this class
{
private:

	// ========== Some Utility Functions (Private Functions) ==========

	int GetCellStartX(const CellPosition& cellpos) const;	// Gets the X coordinate 
															// of the upper left corner of the passed cellpos

	int GetCellStartY(const CellPosition& cellpos) const;	// Gets the Y coordinate 
															// of the upper left corner of the passed cellpos

	void ClearToolBar() const;	// Clears the toolbar by drawing a filled rectangle

public:

	Output();	// A Constructor for any needed initializations

	Input* CreateInput() const;	// Creates a pointer to the Input object	

	// ========== User Interface Functions ==========

	void ClearStatusBar() const;	// Clears the status bar by drawing a filled rectangle

	void ClearGridArea() const;	    // Draws an empty grid (horizontal and vertical lines with empty cells)

	void CreateToolBar(const vector<Button>& buttons) const;		// Create toolbar buttons

	void PrintMessage(string msg) const;	// Prints a message on Status bar

	// ========== Game Drawing Functions ==========

	void DrawCell(const CellPosition& cellpos, CellState state) const;

	~Output();	// A Destructor for any needed deallocations
};
