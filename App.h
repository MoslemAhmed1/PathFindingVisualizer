#pragma once

#include "DEFS.h"
#include "UI_Info.h"

class Input;
class Output;
class Grid;

// Main class that manages everything in the application.
class App
{
	// Pointer to the Grid
	Grid* pGrid;

	// Pointers to the Input and Output 
	Input* pIn;
	Output* pOut;

	bool running;

public:

	App();  // Constructor: where the Input, Ouput and Grid are allocated
	~App(); // Destructor for needed deallocations

	void Run();

	// ========== Interface Management Functions ==========

	Grid* GetGrid() const;    // Returns pointer to the Grid

	void UpdateInterface() const;

	// ========== Action-Related Functions ==========

	void ExecuteAction(ActionType);  // Creates an action of the passed actionType and executes it

};