#pragma once

#include "Grid.h"

class DFS
{
    Output* pOut;
    vector<vector<Cell*>>& G;
    stack<Cell*> mazeStack;
    Cell* startingCell;
    bool done;

public:
    
    DFS(vector<vector<Cell*>>& grid, Output* pOut);
    void Init();
    bool Step();
    bool IsDone() const;
    
private:
    
    void AddRandomNeighbour(Cell* cell);
    vector<Cell*> GetUnvisitedNeighbors(Cell* cell);
    bool isBlocked(Cell* cell);
    // void Algorithm();
};

