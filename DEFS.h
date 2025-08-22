#ifndef DEFS_H
#define DEFS_H

// This file contains some global constants and definitions to be used in the project.

enum ChosenAlgorithm
{
	BFS_ALGORITHM,
	DIJKSTRA_ALGORITHM,
	ASTAR_ALGORITHM
};

enum ActionType
{
	ADD_START,
	ADD_END,
	ADD_WALL,
	CLEAR_GRID,
	// BFS,
	// DIJKSTRA,
	// ASTAR,

	EMPTY,				// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,			// Inside Grid Area
	STATUS 				// Inside StatusBar Area
};

enum CellState 
{
	PATH,
	WALL,
	PENDING,
	VISITED,
	FINAL_PATH
};

#endif