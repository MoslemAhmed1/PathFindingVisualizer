#pragma once

#include "Grid.h"

class BFS
{
    vector<vector<Cell*>>& G;
    Cell* start;
    Cell* end;
    queue<Cell*> frontier;
    vector<Cell*> path;

public:

    BFS(vector<vector<Cell*>>& grid, Cell* start, Cell* end);
    void Init();
    bool Step();
    vector<Cell*> GetPath() const;

private:

    vector<Cell*> BuildPath(Cell* end);
    void AddNeighbours(Cell* cell);

};

/*
Algorithm Explanation:

1- Start with the Start Cell, Check if it's the end :
    - If yes --> return the start cell
    - If not --> 1. Add all the neighbours to the start cell to the queue 
                 2. Set their parent cell to the start cell
                 3. Mark them as pending
                 4. Mark the start cell as visited

2- Loop through all the neighbours in the queue
    - Check if it's the end --> return the path from the end to the start cell (using the parent pointer)
    - If not --> 1. Add all (PATH) neighbours to the current cell to the queue
                 2. Set their parent cell to the current cell
                 3. Mark them as pending
                 4. Mark the current cell as visited
*/