#pragma once

// This file contains some global constants and definitions to be used in the project.
// It also contains common includes which are used in many files
#include "UI_Info.h"
#include "CellPosition.h"
#include "raylib.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <random>
using namespace std;

enum ChosenAlgorithm
{
	BFS_ALGORITHM,
	DIJKSTRA_ALGORITHM,
	ASTAR_ALGORITHM,
	GREEDY_BFS_ALGORITHM,
	GENERATE_MAZE_ALGORITHM,
	NO_CHOSEN_ALGORITHM
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
	RUN_GREEDY_BFS,
	RUN_GENERATE_MAZE,

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
	GREEDY_BFS_BTN,
	GENERATE_MAZE_BTN,
	NONE
};

enum Flag
{ 
	WAITING_FOR_CELL,
	ALGORITHM_RUNNING,
	SETTING_WALLS,
	NO_CURRENT_FLAG
};

enum MazeAlgorithm
{
	DFS_ALGORITHM,
	PRIMS_ALGORITHM,
	NO_MAZE_ALGORITHM
};