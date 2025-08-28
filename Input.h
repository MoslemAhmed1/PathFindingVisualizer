#pragma once

#include "DEFS.h"
#include "UI_Info.h"
#include "raylib.h"
#include "CellPosition.h"

// forward declarations (their includes are in the cpp)
class Output;
class Button;

class Input		// The application manager & grid should have a pointer to this class
{

	vector<Button*> buttons;

public:

	Input(vector<Button*>& buttons);

	// ========== General Functions ==========

	void GetPointClicked(int& x, int& y) const; // Wait for a Mouse Click and Gets the real coordinates (x,y) of it

	// ========== App Functions ==========

	ActionType GetUserAction() const;	 // Reads a user click and map it to its corresponding ActionType

	CellPosition GetCellClicked() const; // Wait for a Mouse Click and Gets the CellPosition of it (VCell and HCell)
									   	 // This function is needed only in Design Mode
										 // If the click is NOT on a cellposition, (-1,-1) is returned
										 // This function is like GetPointClicked but returns Cell Position NOT Real Coordinates

	CellPosition GetCellClicked_F() const;

};