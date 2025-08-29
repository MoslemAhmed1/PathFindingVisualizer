#pragma once
#include "Grid.h"

class Astar
{
    vector<vector<Cell*>>& G;
    Cell* start;
    Cell* end;
    priority_queue<Cell*, vector<Cell*>, CellComparator> frontier;
    double oldCost[NumVerticalCells][NumHorizontalCells];
    vector<Cell*> path;

public:

    Astar(vector<vector<Cell*>>& grid, Cell* start, Cell* end);
    void Init();
    bool Step();
    vector<Cell*> GetPath() const;

private:

    vector<Cell*> BuildPath(Cell* end);

    double heuristic(Cell* next, Cell* end);

    double CalcDistance(double curr_distance, Cell* curr, Cell* next);

    void AddNeighbours(Cell* cell);

};

/*
Algorithm Explanation:

gCost = distance from start cell to current cell
hCost = distance from current cell to end cell
totalCost "fCost" = gCost + hCost

- We perform the same algorithm as Dijkstra, but we compare the totalCost instead of the gCost only
*/