#include "BFS.h"

BFS::BFS(vector<vector<Cell*>>& grid, Cell* start, Cell* end, Output* pOut) : pOut(pOut), G(grid), start(start), end(end), done(false) 
{}

void BFS::Init() 
{
    if (!start || !end) 
        return;
    frontier.push(start);
    start->SetCellState(PENDING);
}

bool BFS::Step() 
{
    if (done || frontier.empty()) 
        return true;

    Cell* cell = frontier.front();
    frontier.pop();

    if (cell == end) 
    {
        path = BuildPath(end);
        done = true;
        return true;
    }

    AddNeighbours(cell);
    cell->SetCellState(VISITED);
    return false;
}

vector<Cell*> BFS::GetPath() const 
{
    return path;
}

bool BFS::IsDone() const 
{
    return done;
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

void BFS::AddNeighbours(Cell* cell) 
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

        Cell* next = G[nx][ny];

        if (next->GetCellState() == PATH || next->GetCellState() == END)
        {
            frontier.push(next);
            G[nx][ny]->SetCellState(PENDING);
            next->SetParentCell(cell);
        }
    }
}