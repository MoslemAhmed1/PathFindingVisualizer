#include "Prim.h"

Prim::Prim(vector<vector<Cell*>>& grid) : G(grid)
{
    isProcessed.resize(grid.size(), vector<bool>(grid[0].size(), 0));

    for (int i = 0; i < G.size(); i++)
        for (int j = 0; j < G[0].size(); j++)
            if (i % 2 == 0 || j % 2 == 0)
                G[i][j]->SetCellState(WALL);
}

void Prim::Init()
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
    AddAdjacentWalls(G[r][c]);
}

bool Prim::Step()
{
    if (wallList.empty())
        return true;

    ConnectNeighbour();

    return false;
}

void Prim::ConnectNeighbour()
{
    if (wallList.empty()) return;

    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<size_t> dis(0, wallList.size() - 1);
    size_t idx = dis(g);
    Cell* wall = wallList[idx];

    int parentX = wall->GetParentCell()->GetCellPosition().VCell();
    int parentY = wall->GetParentCell()->GetCellPosition().HCell();
    int wallX = wall->GetCellPosition().VCell();
    int wallY = wall->GetCellPosition().HCell();
    int dx = wallX - parentX;
    int dy = wallY - parentY;
    int nx = wallX + dx;
    int ny = wallY + dy;

    bool valid = (nx >= 0 && ny >= 0 && nx < G.size() && ny < G[0].size() && G[nx][ny]->GetCellState() == PATH);

    if (valid)
    {
        wall->SetCellState(VISITED);       // Convert Wall to Path
        G[nx][ny]->SetCellState(VISITED);  // Mark Neighbor as Visited
        AddAdjacentWalls(G[nx][ny]);
    }

    // Remove the picked wall
    wallList[idx] = wallList.back();
    wallList.pop_back();
}

void Prim::AddAdjacentWalls(Cell* cell)
{
    int x = cell->GetCellPosition().VCell();
    int y = cell->GetCellPosition().HCell();

    int dr[4] = { 0, -1, 0, 1 };
    int dc[4] = { -1, 0, 1, 0 };

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dr[i];
        int ny = y + dc[i];
        if (nx >= 0 && ny >= 0 && nx < G.size() && ny < G[0].size() && G[nx][ny]->GetCellState() == WALL && !isProcessed[nx][ny])
        {
            G[nx][ny]->SetParentCell(cell);
            wallList.push_back(G[nx][ny]);
            isProcessed[nx][ny] = true;
        }
    }
}

/*

NOTE : This was the original function which was then broken down
        into 2 functions : Init() and Step().


void Prim::Algorithm()
{
    // Note : PATHS = Odd Coordinates , WALLS = Even Coordinates
    // 1- Choose a random cell to start with --> Mark as Visited --> Add its adjacent walls to a list
    // 2- Choose a random wall adjacent the starting cell --> 
    //      if it separates the visited cell from an unvisited cell -> remove the wall(mark it as visited)
    //      else remove it from the list (keep it as wall)
    // 3- Keep repeating [2.] till all cells are visited (All neighbours are visited)

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
    } while (r % 2 == 0 || c % 2 == 0);

    G[r][c]->SetCellState(VISITED);
    AddAdjacentWalls(G[r][c]);


    // Step 2 : Add Random Unvisited Neighbour, this is converted to Step() function
    while (!wallList.empty())
    {
        ConnectNeighbour();
    }
}
*/