#pragma once

#include "Grid.h"

class BFS
{

    Output* pOut;

public:

    BFS(vector<vector<Cell*>> grid, Cell* start, Cell* end, vector<Cell*>& path, Output* pOut);

    vector<Cell*> BuildPath(Cell* end);

    void AddNeighbours(queue<Cell*>& frontier, Cell* cell, vector<vector<Cell*>>& G);

    vector<Cell*> ApplyAlgorithm(vector<vector<Cell*>>& G, Cell* start, Cell* end);

};