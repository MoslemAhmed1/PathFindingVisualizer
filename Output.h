#pragma once

#include "Button.h"

// forward declarations (their includes are in the cpp)
class Input;

class Output
{

private:

	vector<Button*> buttons; // Store buttons for redrawing

	Texture2D icons[9];		 // Load Button Textures (images)

	Font font;				 // Load custom font


	// ========== Some Utility Functions (Private Functions) ========== //

	int GetCellStartX(const CellPosition& cellpos) const;	// Gets the X coordinate 
															// of the upper left corner of the passed cellpos

	int GetCellStartY(const CellPosition& cellpos) const;	// Gets the Y coordinate 
															// of the upper left corner of the passed cellpos

	void ClearToolBar() const;	// Clears the toolbar by drawing a filled rectangle

public:

	Output(vector<Button*>& buttons);

	Input* CreateInput(vector<Button*>& buttons) const;	// Creates a pointer to the Input object	

	// ========== User Interface Functions ========== //

	void ClearStatusBar() const;	// Clears the status bar by drawing a filled rectangle

	void ClearGridArea() const;	    // Draws all grid cells

	void CreateToolBar() const;		// Create toolbar buttons

	void PrintMessage(string msg) const;	// Prints a message on Status bar

	// ========== Drawing Functions ========== //

	void DrawCell(const CellPosition& cellpos, CellState state, bool isStart = false, bool isEnd = false) const;

	~Output();
};
