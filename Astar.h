#pragma once
#include "Grid.h"

class Astar
{

    Output* pOut;

public:

    Astar(vector<vector<Cell*>> grid, Cell* start, Cell* end, vector<Cell*>& path, Output* pOut);

    vector<Cell*> BuildPath(Cell* end);

    // Use Octile distance for 8-direction movement
    double heuristic(Cell* next, Cell* end);

    double CalcDistance(double curr_distance, Cell* curr, Cell* next);

    void AddNeighbours(priority_queue<Cell*>& frontier, Cell* cell, Cell* end, vector<vector<Cell*>>& G);

    vector<Cell*> ApplyAlgorithm(vector<vector<Cell*>>& G, Cell* start, Cell* end);

};