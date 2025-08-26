#pragma once

#include "DEFS.h"
#include "UI_Info.h"
#include "Button.h"

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

	vector<Button*> buttons;

public:

	App();  // Constructor: where the Input, Ouput and Grid are allocated
	~App(); // Destructor for needed deallocations

	void Run();

	// ========== Interface Management Functions ==========

	Grid* GetGrid() const;    // Returns pointer to the Grid

	void UpdateInterface() const;

	// ========== Action-Related Functions ==========

	void ExecuteAction(ActionType ActType);  // Creates an action of the passed actionType and executes it
	// To execute an action :
	// 1- Get the ActionType
	// 2- Read its parameters
	// 3- Proceed with execution logic
	void AddStart();
	void AddEnd();
	void AddWall();
	void ClearGrid();
	void Run_BFS();
	void Run_Dijkstra();
	void Run_AStar();
};