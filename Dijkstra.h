#pragma once
#include "Grid.h"

// In dijkstra, the the class Cell datamembers totalCost == gCost 
// (because the comparator compares totalCost, and since it's not used in dijkstra, i chose to make it equal the gCost)
class Dijkstra
{
    vector<vector<Cell*>>& G;
    Cell* start;
    Cell* end;
    priority_queue<Cell*, vector<Cell*>, CellComparator> frontier; // Min-heap
    double oldCost[NumVerticalCells][NumHorizontalCells];
    vector<Cell*> path;

public:
    
    Dijkstra(vector<vector<Cell*>>& grid, Cell* start, Cell* end);
    void Init();
    bool Step();
    vector<Cell*> GetPath() const;;

private:

    vector<Cell*> BuildPath(Cell* end);

    double CalcDistance(double curr_distance, Cell* curr, Cell* next);

    void AddNeighbours(Cell* cell);

};

/*
Algorithm Explanation:

1- Start with the Start Cell, Set its weight to zero, Check if it's the end :
    - If yes --> return the start cell
    - If not --> 1. Add all the neighbours to the start cell to the queue
                 2. Set their parent cell to the start cell
                 3. Mark them as pending
                 4. Mark the start cell as visited

2- Loop through all the neighbours in the queue
    - Check if it's the end --> return the path from the end to the start cell (using the parent pointer)
    - If not --> 1. Calculate the distance between the neighbours and the start cell, update their cost, save their cost to the oldCost array
                 2. Add all (PATH) neighbours to the current cell to the queue
                 3. Add any (PENDING) neighbours to the current cell IF their newCost(from a different path) is less than their oldCost(from the oldCost array)
                 3. Set their parent cell to the current cell
                 4. Mark them as pending
                 5. Mark the current cell as visited
*/