#pragma once

#include "DEFS.h"

// forward declarations (their includes are in the cpp)
class Output;
class Button;

class Input
{

	vector<Button*> buttons;

public:

	Input(vector<Button*>& buttons);

	void GetPointClicked(int& x, int& y) const; // Wait for a Mouse Click and Gets the real coordinates (x,y) of it

	CellPosition GetCellClicked() const;		// Wait for a Mouse Click and Gets the CellPosition of it (VCell and HCell)
												// This function is like GetPointClicked but returns Cell Position NOT Real Coordinates

	CellPosition GetCellClicked_F() const;		// This is a modified version of GetCellClicked to be used for Wall Setting Mode

	ActionType GetUserAction() const;			// Reads a user click and map it to its corresponding ActionType

};