#ifndef DEFS_H
#define DEFS_H

// This file contains some global constants and definitions to be used in the project.
#include "UI_Info.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

enum ChosenAlgorithm
{
	BFS_ALGORITHM,
	DIJKSTRA_ALGORITHM,
	ASTAR_ALGORITHM
};

enum ActionType
{
	RUN_BFS,
	RUN_DIJKSTRA,
	RUN_ASTAR,
	ADD_WALL,
	ADD_START,
	ADD_END,
	CLEAR_GRID,

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
	START,
	END,
	FINAL_PATH
};

enum ButtonType
{
	BFS_BTN,
	DIJKSTRA_BTN,
	ASTAR_BTN,
	ADD_WALL_BTN,
	ADD_START_BTN,
	ADD_END_BTN,
	CLEAR_GRID_BTN,
	NONE
};

#endif