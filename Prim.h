#pragma once

#include "Grid.h"

class Prim
{
    vector<vector<Cell*>>& G;
    vector<Cell*> wallList;
    vector<vector<bool>> isProcessed;

public:

    Prim(vector<vector<Cell*>>& grid);
    void Init();
    bool Step();

private:

    void ConnectNeighbour();
    void AddAdjacentWalls(Cell* cell);
    // void Algorithm();
};

/*
Algorithm Explanation :
    // Note : PATHS = BOTH Odd Coordinates , WALLS = Either Even Coordinates
    
    // 1- Choose a random cell to start with --> Mark as Visited --> Add its adjacent walls to a list
    
    // 2- Choose a random wall adjacent the starting cell -->
    //      if it separates the visited cell from an unvisited cell -> remove the wall(mark it as visited)
    //      else remove it from the list (keep it as wall)
    
    // 3- Keep repeating [2.] till all cells are visited (All neighbours are visited)
*/
