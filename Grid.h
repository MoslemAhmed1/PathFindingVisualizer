#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

#include "UI_Info.h"
#include "DEFS.h"
#include "Cell.h"
using namespace std;

// #include "Input.h"
// #include "Output.h"
// #include <fstream>


// forward declarations (the includes are in the cpp)
class Cell;

class Grid
{
	// Output* pOut;   // A pointer to the Output object
	// Input* pIn;     // A pointer to the Input object

	vector<vector<Cell*>> grid;		// An array of "Pointers" to All Cells of the Grid Cells
	
	Cell* start;
	Cell* end;



public:

	Grid();								// Gives the Grid a Pointer to the Output Object and the Input Object
										// and makes any needed initializations

// ========= Common Algorithm Functions ========= //

	vector<Cell*> GetPath(ChosenAlgorithm algorithm);

	void PrintPath(ChosenAlgorithm algorithm);

	void PrintGrid();

// ========= Others ========= //

	void AddWalls();

	void SetStartCell(int r, int c);
	void SetEndCell(int r, int c);


// ========= Setters and Getters Functions ========= //

	// Input* GetInput() const;	// Gets a Pointer to the Input
	// Output* GetOutput() const; // Gets a Pointer to the Output 

// ========= User Interface Functions ========= //

	void UpdateInterface() const;	// It Updates the Grid according to the last state of the game
									// In Design mode, it draws all cells/cards THEN all ladders/snakes THEN all players
									// In Play mode, it only draws the player's info on the right side of the toolbar
									// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
									//       and the cards/snakes/ladders positions do NOT change already in Play Mode

	// void PrintErrorMessage(string msg); // Prints an error message on statusbar, Waits for mouse click then clears statusbar
										// We added this function once here because it is used many times by other classes

// ===================== Additional Functions ===================== //

	void ClearGrid();

// ================================================================ //

	~Grid(); // A destructor for any needed deallcations
};
