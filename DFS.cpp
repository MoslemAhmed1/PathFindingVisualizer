#include "DFS.h"

DFS::DFS(vector<vector<Cell*>>& grid) : G(grid)
{
    for (int i = 0; i < G.size(); i++)
        for (int j = 0; j < G[0].size(); j++)
            if (i % 2 == 0 || j % 2 == 0)
                G[i][j]->SetCellState(WALL);
}

void DFS::Init()
{
    int r, c;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disV(0, NumVerticalCells - 1);
    uniform_int_distribution<> disH(0, NumHorizontalCells - 1);
    do
    {
        r = disV(gen);
        c = disH(gen);
    } while (r % 2 == 0 || c % 2 == 0);

    G[r][c]->SetCellState(VISITED);
    mazeStack.push(G[r][c]);
}

bool DFS::Step()
{
    if (mazeStack.empty())
        return true;

    AddRandomNeighbour(mazeStack.top());

    return false;
}

bool DFS::isBlocked(Cell* cell)
{
    return GetUnvisitedNeighbors(cell).empty();
}

vector<Cell*> DFS::GetUnvisitedNeighbors(Cell* cell)
{
    int x = cell->GetCellPosition().VCell();
    int y = cell->GetCellPosition().HCell();

    int dr[4] = { 0, -2, 0, 2 };
    int dc[4] = { -2, 0, 2, 0 };

    vector<Cell*> neighbors;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dr[i];
        int ny = y + dc[i];
        if (nx >= 0 && ny >= 0 && nx < G.size() && ny < G[0].size() && G[nx][ny]->GetCellState() == PATH)
        {
            neighbors.push_back(G[nx][ny]);
        }
    }

    return neighbors;
}

void DFS::AddRandomNeighbour(Cell* cell)
{
    // Pop blocked cells from top of stack (Backtracking)
    while (!mazeStack.empty() && isBlocked(mazeStack.top())) 
        mazeStack.pop();

    if (mazeStack.empty()) 
        return;  // done

    // top (cell) has unvisited neighbors
    cell = mazeStack.top();

    // Get and shuffle unvisited neighbors
    auto neighbors = GetUnvisitedNeighbors(cell);
    random_device rd;
    mt19937 g(rd());
    shuffle(neighbors.begin(), neighbors.end(), g);

    // Pick first (random)
    Cell* neighbour = neighbors[0];
    int dx = neighbour->GetCellPosition().VCell() - cell->GetCellPosition().VCell();
    int dy = neighbour->GetCellPosition().HCell() - cell->GetCellPosition().HCell();
    int nxW = cell->GetCellPosition().VCell() + dx / 2;
    int nyW = cell->GetCellPosition().HCell() + dy / 2;

    G[nxW][nyW]->SetCellState(VISITED);  // convert wall to path
    neighbour->SetCellState(VISITED);   // mark unvisited neighbour as visited
    mazeStack.push(neighbour);
}

/*
NOTE : This was the original function which was then broken down
        into 2 functions : Init() and Step().

void DFS::Algorithm()
{
    // Note : PATHS = Odd Coordinates , WALLS = Even Coordinates
    // 1- Choose a random cell to start with --> Mark as Visited --> Push to Stack
    // 2- Choose a random UNVISITED neighbour to the starting cell --> Mark as Visited --> Push to Stack
    // 3- Keep repeating [2.] till reaching a blocked path (All neighbours are visited)
    // 4- If reached a blocked path, backtrack till finding a cell with an unvisited neighbour.

    // Step 1 : Initialization, this is converted to Init() function
    int r, c;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disV(0, NumVerticalCells - 1);
    uniform_int_distribution<> disH(0, NumHorizontalCells - 1);
    do 
    {
        r = disV(gen);
        c = disH(gen);
    } 
    while (r % 2 == 0 || c % 2 == 0);
    
    G[r][c]->SetCellState(VISITED);
    mazeStack.push(G[r][c]);

    // Step 2 : Add Random Unvisited Neighbour, this is converted to Step() function
    while (!mazeStack.empty())
    {
        AddRandomNeighbour(mazeStack.top());
    }

}

*/