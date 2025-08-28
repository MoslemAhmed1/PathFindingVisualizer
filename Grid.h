#pragma once

#include "DEFS.h"
#include "Cell.h"

#include "Input.h"
#include "Output.h"
#include <fstream>


// forward declarations (the includes are in the cpp)
class Cell;
class BFS;
class Dijkstra;
class Astar;
class GreedyBFS;

class Grid
{
	Output* pOut;   
	Input* pIn;     

	vector<vector<Cell*>> grid;		// An array of "Pointers" to All Cells of the Grid Cells
	
	Cell* start;
	Cell* end;

	string msg;

	ChosenAlgorithm currentAlgorithm;
	BFS* bfs;
	Dijkstra* dijkstra;
	Astar* astar;
	GreedyBFS* greedyBFS;
	bool algorithmRunning;

public:

	Grid(Input* pIn, Output* pOut);		// Gives the Grid a Pointer to the Output Object and the Input Object
										// and makes any needed initializations

// ========= Common Algorithm Functions ========= //

	void GetPath(ChosenAlgorithm algorithm);

	void StepAlgorithm();

	void PrintPath(ChosenAlgorithm algorithm);

// ========= Others ========= //

	bool SetStartCell(int r, int c);
	bool SetEndCell(int r, int c);
	bool SetWallCell(int r, int c);

// ========= Setters and Getters Functions ========= //

	Input* GetInput() const;	// Gets a Pointer to the Input
	Output* GetOutput() const; // Gets a Pointer to the Output 

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

	~Grid(); // A destructor for any needed deallcations
};
