#pragma once
#include "Grid.h"

class Dijkstra
{
    Output* pOut;
    vector<vector<Cell*>>& G;
    Cell* start;
    Cell* end;
    priority_queue<Cell*> frontier;
    bool done;
    vector<Cell*> path;

public:
    
    Dijkstra(vector<vector<Cell*>>& grid, Cell* start, Cell* end, Output* pOut);
    void Init();
    bool Step(); // Process one node, return true if done
    vector<Cell*> GetPath() const;
    bool IsDone() const;

private:

    vector<Cell*> BuildPath(Cell* end);

    double CalcDistance(double curr_distance, Cell* curr, Cell* next);

    void AddNeighbours(Cell* cell);

};