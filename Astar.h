#pragma once
#include "Grid.h"

class Astar
{

    Output* pOut;
    vector<vector<Cell*>>& G;
    Cell* start;
    Cell* end;
    priority_queue<Cell*, vector<Cell*>, CellComparator> frontier;
    float oldCost[NumVerticalCells][NumHorizontalCells];
    bool done;
    vector<Cell*> path;

public:

    Astar(vector<vector<Cell*>>& grid, Cell* start, Cell* end, Output* pOut);
    void Init();
    bool Step(); // Process one node, return true if done
    vector<Cell*> GetPath() const;

private:

    vector<Cell*> BuildPath(Cell* end);

    // Use Octile distance for 8-direction movement
    double heuristic(Cell* next, Cell* end);

    double CalcDistance(double curr_distance, Cell* curr, Cell* next);

    void AddNeighbours(Cell* cell);

};