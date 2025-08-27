#pragma once

#include "Grid.h"

class BFS
{
    Output* pOut;
    vector<vector<Cell*>>& G;
    Cell* start;
    Cell* end;
    queue<Cell*> frontier;
    bool done;
    vector<Cell*> path;

public:

    BFS(vector<vector<Cell*>>& grid, Cell* start, Cell* end, Output* pOut);
    void Init();
    bool Step(); // Process one node, return true if done
    vector<Cell*> GetPath() const;
    bool IsDone() const;

private:

    vector<Cell*> BuildPath(Cell* end);
    void AddNeighbours(Cell* cell);

};