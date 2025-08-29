#pragma once

#include "DEFS.h"
#include "Cell.h"

#include "Input.h"
#include "Output.h"

// forward declarations (the includes are in the cpp)
class Cell;
class BFS;
class Dijkstra;
class Astar;
class GreedyBFS;
class DFS;
class Prim;

class Grid
{
	Output* pOut;   
	Input* pIn;     

	vector<vector<Cell*>> grid;	// An array of "Pointers" to All Cells of the Grid Cells
	
	Cell* start;
	Cell* end;

	string msg;	// Stores the last message printed

	// Algorithm Control Flags
	ChosenAlgorithm currentAlgorithm;
	bool algorithmRunning;

	// Shortest Path Algorithms
	BFS* bfs;
	Dijkstra* dijkstra;
	Astar* astar;
	GreedyBFS* greedyBFS;

	// Maze Generation Algorithms
	DFS* dfs;
	Prim* prim;

public:

	Grid(Input* pIn, Output* pOut);		// Gives the Grid a Pointer to the Output Object and the Input Object
										// and makes any needed initializations

// ========= Common Algorithm Functions ========= //

	void StepAlgorithm();

	void GetPath(ChosenAlgorithm algorithm);

	void PrintPath(ChosenAlgorithm algorithm);

	void GenerateMaze(MazeAlgorithm algorithm);

// ========= Setters and Getters Functions ========= //

	bool SetStartCell(int r, int c);
	bool SetEndCell(int r, int c);
	bool SetWallCell(int r, int c);

	Input* GetInput() const;
	Output* GetOutput() const;

	Cell* GetStartCell() const;
	Cell* GetEndCell() const;

	string GetMessage() const;

	bool IsAlgorithmRunning() const;

// ========= User Interface Functions ========= //

	void UpdateInterface() const;	// It Updates the Grid according to the last state of the game

	void PrintMessage(string msg); // Prints a message on statusbar, Waits for mouse click then clears statusbar
									
// ===================== Additional Functions ===================== //

	void ClearGrid();

	void ClearPath();

// ================================================================ //

	~Grid();
};
