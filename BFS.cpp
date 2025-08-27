#include "BFS.h"

BFS::BFS(vector<vector<Cell*>> grid, Cell* start, Cell* end, vector<Cell*>& path, Output* pOut) : pOut(pOut)
{
    path = ApplyAlgorithm(grid, start, end);
}

vector<Cell*> BFS::BuildPath(Cell* end)
{
    if (!end->GetParentCell())
        return {};

    vector<Cell*> path;

    for (Cell* cur = end; cur != nullptr; cur = cur->GetParentCell())
    {
        path.push_back(cur);
    }

    reverse(path.begin(), path.end());
    return path;
}

void BFS::AddNeighbours(queue<Cell*>& frontier, Cell* cell, vector<vector<Cell*>>& G)
{
    int x = cell->GetCellPosition().VCell();
    int y = cell->GetCellPosition().HCell();

    int dr[4] = { 0, -1, 0, 1 };
    int dc[4] = { -1, 0, 1, 0 };

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dr[i];
        int ny = y + dc[i];

        if (nx < 0 || ny < 0 || nx >= G.size() || ny >= G[0].size())
            continue;

        Cell* current = cell;
        Cell* next = G[nx][ny];

        if (G[nx][ny]->GetCellState() == PATH)
        {
            frontier.push(next);
            G[nx][ny]->SetCellState(PENDING);
            next->SetParentCell(current);
            BeginDrawing();
            pOut->DrawCell(next->GetCellPosition(), PENDING); // Draw pending cell
            EndDrawing();
            WaitTime(0.01); // 10ms delay for visualization
        }
    }
}

vector<Cell*> BFS::ApplyAlgorithm(vector<vector<Cell*>>& G, Cell* start, Cell* end)
{
    if (!start || !end)
        return {};

    if (start == end)
        return { start };

    // 1- Create frontier queue
    int rows = G.size(), cols = G[0].size();
    queue<Cell*> frontier;

    // 2- Process the start node
    frontier.push(start);
    start->SetCellState(PENDING);

    // Loop through all neighbours
    while (!frontier.empty())
    {

        Cell* cell = frontier.front();
        frontier.pop();


        if (cell == end)
            return BuildPath(end);

        AddNeighbours(frontier, cell, G);
        cell->SetCellState(VISITED);
        BeginDrawing();
        pOut->DrawCell(cell->GetCellPosition(), VISITED); // Draw visited cell
        EndDrawing();
        WaitTime(0.01); // 10ms delay for visualization
    }

    return {};
}