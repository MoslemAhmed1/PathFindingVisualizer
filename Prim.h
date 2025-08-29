#pragma once

#include "Grid.h"

class Prim
{
    Output* pOut;
    vector<vector<Cell*>>& G;
    vector<Cell*> wallList;
    vector<vector<bool>> isProcessed;

public:

    Prim(vector<vector<Cell*>>& grid, Output* pOut);
    void Init();
    bool Step();

private:

    void ConnectNeighbour();
    void AddAdjacentWalls(Cell* cell);
    // void Algorithm();
};
