#pragma once
#include "Grid.h"

// Greedy Best-First-Search
class GreedyBFS
{
    vector<vector<Cell*>>& G;
    Cell* start;
    Cell* end;
    priority_queue<Cell*, vector<Cell*>, CellComparator> frontier;
    double oldCost[NumVerticalCells][NumHorizontalCells]; // Stores the old cost for comparison
    vector<Cell*> path;

public:

    GreedyBFS(vector<vector<Cell*>>& grid, Cell* start, Cell* end);
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

- Here, we only use the hCost (distance from the current cell to the end cell) for comparison
- We perform the same algorithm as Dijkstra/Astar, but we compare the hCost instead of the gCost or totalCost
*/