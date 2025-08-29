#pragma once

#include "DEFS.h"
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

	ActionType pendingAction; // Store the action waiting for a cell click

	Flag currentFlag;	// Flag to separate different inputs

public:

	App();  
	~App(); 

	void Run();

	// ========== Action-Related Functions ==========

	void ExecuteAction(ActionType ActType);  // Creates an action of the passed actionType and executes it
	void ExecGridAction(ActionType ActType, CellPosition position); // New method for grid actions
	
	// To execute an action :
	// 1- Get the ActionType
	// 2- Read its parameters
	// 3- Proceed with execution logic

	void AddStart();
	void AddEnd();
	void AddWall();
	void Run_BFS();
	void Run_Dijkstra();
	void Run_AStar();
	void Run_GreedyBFS();
	void Run_Generate_Maze();

};