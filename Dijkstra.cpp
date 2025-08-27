#include "Dijkstra.h"

Dijkstra::Dijkstra(vector<vector<Cell*>>& grid, Cell* start, Cell* end, Output* pOut) : pOut(pOut), G(grid), start(start), end(end), done(false)
{}

void Dijkstra::Init()
{
    if (!start || !end)
        return;
    frontier.push(start);
    start->SetCellState(PENDING);
    start->SetTotalCost(0);
}

bool Dijkstra::Step()
{
    if (done || frontier.empty())
        return true;

    Cell* cell = frontier.top();
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

vector<Cell*> Dijkstra::GetPath() const
{
    return path;
}

vector<Cell*> Dijkstra::BuildPath(Cell* end)
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

double Dijkstra::CalcDistance(double curr_distance, Cell* curr, Cell* next)
{
    CellPosition currP = curr->GetCellPosition();
    CellPosition nextP = next->GetCellPosition();
    if ((currP.HCell() == nextP.HCell()) || (currP.VCell() == nextP.VCell()))
        return curr_distance + 1;
    else
        return curr_distance + sqrt(2);
}

void Dijkstra::AddNeighbours(Cell* cell)
{
    int x = cell->GetCellPosition().VCell();
    int y = cell->GetCellPosition().HCell();

    int dr[8] = { 0, -1, 0, 1, -1, -1, 1, 1 };
    int dc[8] = { -1, 0, 1, 0, -1, 1, -1, 1 };
    int max_i = 4; // Change to 8 for diagonal

    for (int i = 0; i < max_i; i++)
    {
        int nx = x + dr[i];
        int ny = y + dc[i];

        if (nx < 0 || ny < 0 || nx >= G.size() || ny >= G[0].size() || G[nx][ny]->GetCellState() == WALL || G[nx][ny]->GetCellState() == VISITED)
            continue;

        /*
        Diagonal Check :
        1 - Up Left(-1, -1)
            - Check(-1, 0) & (0, -1)
            2 - Up Right(-1, 1)
            - Check(-1, 0) & (0, 1)
            3 - Down Right(1, 1)
            - Check(0, 1) & (1, 0)
            4 - Down Left(1, -1)
            - Check(0, -1) & (1, 0)
        */
        if ((dr[i] == -1 && dc[i] == -1 && (G[x - 1][y]->GetCellState() == WALL && G[x][y - 1]->GetCellState() == WALL)) ||
            (dr[i] == -1 && dc[i] == 1 && (G[x - 1][y]->GetCellState() == WALL && G[x][y + 1]->GetCellState() == WALL)) ||
            (dr[i] == 1 && dc[i] == 1 && (G[x][y + 1]->GetCellState() == WALL && G[x + 1][y]->GetCellState() == WALL)) ||
            (dr[i] == 1 && dc[i] == -1 && (G[x][y - 1]->GetCellState() == WALL && G[x + 1][y]->GetCellState() == WALL)))
            continue;
        

        Cell* next = G[nx][ny];
        double newCost = CalcDistance(cell->GetTotalCost(), cell, next);

        bool isEnd = (next->GetCellState() == END);
        if (next->GetCellState() == PATH || isEnd || (next->GetCellState() == PENDING && newCost < next->GetTotalCost()))
        {
            next->SetTotalCost(newCost);
            G[nx][ny]->SetCellState(PENDING);
            next->SetParentCell(cell);
            frontier.push(next);
        }
    }
}