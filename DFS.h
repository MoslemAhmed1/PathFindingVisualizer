#pragma once

#include "Grid.h"

class DFS
{
    vector<vector<Cell*>>& G;
    stack<Cell*> mazeStack;

public:
    
    DFS(vector<vector<Cell*>>& grid);
    void Init();
    bool Step();
    
private:
    
    void AddRandomNeighbour(Cell* cell);
    vector<Cell*> GetUnvisitedNeighbors(Cell* cell);
    bool isBlocked(Cell* cell);
    // void Algorithm();
};

/*
Algorithm Explanation:
    // Note : PATHS = Odd Coordinates , WALLS = Even Coordinates

    // 1- Choose a random cell to start with --> Mark as Visited --> Push to Stack
    
    // 2- Choose a random UNVISITED neighbour to the starting cell --> Mark as Visited --> Push to Stack
    
    // 3- Keep repeating [2.] till reaching a blocked path (All neighbours are visited)
    
    // 4- If reached a blocked path, backtrack till finding a cell with an unvisited neighbour.
*/