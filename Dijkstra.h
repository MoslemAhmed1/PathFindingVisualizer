#pragma once
#include "Grid.h"

class Dijkstra
{

    Output* pOut;

public:
    
    Dijkstra(vector<vector<Cell*>> grid, Cell* start, Cell* end, vector<Cell*>& path, Output* pOut);

    vector<Cell*> BuildPath(Cell* end);

    double CalcDistance(double curr_distance, Cell* curr, Cell* next);

    void AddNeighbours(priority_queue<Cell*>& frontier, Cell* cell, vector<vector<Cell*>>& G);

    vector<Cell*> ApplyAlgorithm(vector<vector<Cell*>>& G, Cell* start, Cell* end);

};