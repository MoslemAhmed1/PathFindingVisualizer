#include "Dijkstra.h"

Dijkstra::Dijkstra(vector<vector<Cell*>> grid, Cell* start, Cell* end, vector<Cell*>& path, Output* pOut) : pOut(pOut)
{       
    path = ApplyAlgorithm(grid, start, end);
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

void Dijkstra::AddNeighbours(priority_queue<Cell*>& frontier, Cell* cell, vector<vector<Cell*>>& G)
{
    int x = cell->GetCellPosition().VCell();
    int y = cell->GetCellPosition().HCell();

    int dr[8] = { 0, -1, 0, 1, -1, -1, 1, 1 };
    int dc[8] = { -1, 0, 1, 0, -1, 1, -1, 1 };

    for (int i = 0; i < 4; i++)
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

            if ((dr[i] == -1 && dc[i] == -1 && (G[x - 1][y].GetCellState() == WALL && G[x][y - 1].GetCellState() == WALL)) ||
                (dr[i] == -1 && dc[i] == 1 && (G[x - 1][y].GetCellState() == WALL && G[x][y + 1].GetCellState() == WALL)) ||
                (dr[i] == 1 && dc[i] == 1 && (G[x][y + 1].GetCellState() == WALL && G[x + 1][y].GetCellState() == WALL)) ||
                (dr[i] == 1 && dc[i] == -1 && (G[x][y - 1].GetCellState() == WALL && G[x + 1][y].GetCellState() == WALL)))
                continue;
        */

        Cell* current = cell;
        Cell* next = G[nx][ny];
        // double newCost = calc_distance(cell.Get_G_Cost(), current, next);
        double newCost = cell->GetTotalCost() + 1;

        if (G[nx][ny]->GetCellState() == PATH)
        {
            next->SetTotalCost(newCost);
            G[nx][ny]->SetCellState(PENDING);
            next->SetParentCell(current);
            frontier.push(next);
            BeginDrawing();
            pOut->DrawCell(cell->GetCellPosition(), PENDING); // Draw pending cell
            EndDrawing();
            WaitTime(0.01); // 10ms delay for visualization
        }
        if (G[nx][ny]->GetCellState() == PENDING)
        {
            if (newCost < next->GetTotalCost())
            {
                next->SetParentCell(current);
                next->SetTotalCost(newCost);
                frontier.push(next);
            }
        }
    }
}

vector<Cell*> Dijkstra::ApplyAlgorithm(vector<vector<Cell*>>& G, Cell* start, Cell* end)
{
    if (!start || !end)
        return {};

    // 1- Create frontier queue, parent array, distance array(weight)
    int rows = G.size(), cols = G[0].size();
    priority_queue<Cell*> frontier;

    // 2- Process the start node
    start->SetTotalCost(0);
    frontier.push(start);

    if (start == end)
        return { start };

    // Loop through all neighbours
    while (!frontier.empty())
    {
        Cell* cell = frontier.top();
        frontier.pop();

        if (cell == end)
            return BuildPath(end);

        if (cell->GetTotalCost() > G[cell->GetCellPosition().VCell()][cell->GetCellPosition().HCell()]->GetTotalCost())
            continue;

        AddNeighbours(frontier, cell, G);
        cell->SetCellState(VISITED);
        BeginDrawing();
        pOut->DrawCell(cell->GetCellPosition(), VISITED); // Draw visited cell
        EndDrawing();
        WaitTime(0.01); // 10ms delay for visualization
    }

    return {};
}