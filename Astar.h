#pragma once
#include "Grid.h"

class Astar
{

public:

    Astar(vector<vector<Cell*>> grid, Cell* start, Cell* end, vector<Cell*>& path);

    vector<Cell*> BuildPath(Cell* end);

    // Use Octile distance for 8-direction movement
    double heuristic(Cell* next, Cell* end);

    double CalcDistance(double curr_distance, Cell* curr, Cell* next);

    void AddNeighbours(priority_queue<Cell*>& frontier, Cell* cell, Cell* end, vector<vector<Cell*>>& G);

    vector<Cell*> ApplyAlgorithm(vector<vector<Cell*>>& G, Cell* start, Cell* end);

};

/*

Each Cell/Node stores 3 values:
	g : distance between the current node and the start node
	h : distance between the current node and the end node
	f : g + h

*/

// AStar OOP

/*

// Use Octile distance for 8-direction movement
double heuristic(Cell* next, Cell* end)
{
    CellPosition nextP = next->GetCellPosition();
    CellPosition endP = end->GetCellPosition();
    double dx = abs(endP.VCell() - nextP.VCell());
    double dy = abs(endP.HCell() - nextP.HCell());
    return (dx + dy) + (sqrt(2) - 2) * min(dx, dy);
}

double calc_distance(double curr_distance, Cell* curr, Cell* next)
{
    CellPosition currP = curr->GetCellPosition();
    CellPosition nextP = next->GetCellPosition();
    if ((currP.HCell() == nextP.HCell()) || (currP.VCell() == nextP.VCell()))
        return curr_distance + 1;
    else
        return curr_distance + sqrt(2);
}

void add_neighbours(priority_queue<Cell*>& frontier, Cell* cell, Cell* end, vector<vector<Cell*>>& G)
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

        //
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
        //

Cell* current = cell;
Cell* next = G[nx][ny];
// double newCost = calc_distance(cell.Get_G_Cost(), current, next);
double newCost = cell->Get_G_Cost() + 1;
double priority = newCost + heuristic(next, end);


if (G[nx][ny]->GetCellState() == PATH)
{
    frontier.push(next);
    G[nx][ny]->SetCellState(PENDING);
    next->Set_G_Cost(newCost);
    next->Set_H_Cost(priority - newCost);
    next->SetTotalCost(priority);
}
if (G[nx][ny]->GetCellState() == PENDING)
{
    if (priority < next->GetTotalCost())
    {
        frontier.push(next);
        next->Set_G_Cost(newCost);
        next->Set_H_Cost(priority - newCost);
        next->SetTotalCost(priority);
    }
}
    }
}

vector<Cell*> A_Star(vector<vector<Cell*>>& G, Cell* start, Cell* end)
{
    // 1- Create frontier queue, parent array, distance array(weight)
    int rows = G.size(), cols = G[0].size();
    priority_queue<Cell*> frontier;

    // 2- Process the start node
    start->Set_G_Cost(0);
    start->Set_H_Cost(0);
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
            return build_path(start, end);

        if (cell->GetTotalCost() > G[cell->GetCellPosition().VCell()][cell->GetCellPosition().HCell()]->GetTotalCost())
            continue;

        add_neighbours(frontier, cell, end, G);
        cell->SetCellState(VISITED);
    }

    return {}; // no path found
}

*/


// AStar Normal

/*
// Use Octile distance for 8-direction movement
double heuristic(pair<int, int> next, pair<int, int> end)
{
    double dx = abs(end.first - next.first);
    double dy = abs(end.second - next.second);
    return (dx + dy) + (sqrt(2) - 2) * min(dx, dy);
}

double calc_distance(double curr_distance, pair<int, int> curr, pair<int, int> next)
{
    if ((curr.first == next.first) || (curr.second == next.second))
        return curr_distance + 1;
    else
        return curr_distance + sqrt(2);
}

void add_neighbours(priority_queue<pair<double, pair<int, int>>>& frontier, pair<int, pair<int, int>> cell, pair<int, int> end, vector<vector<CellState>>& G, vector<vector<double>>& dist, vector<vector<pair<int, int>>>& parent)
{
    int x = cell.second.first;
    int y = cell.second.second;

    int dr[8] = { 0, -1, 0, 1, -1, -1, 1, 1 };
    int dc[8] = { -1, 0, 1, 0, -1, 1, -1, 1 };

    for (int i = 0; i < 8; i++)
    {
        int nx = x + dr[i];
        int ny = y + dc[i];

        if (nx < 0 || ny < 0 || nx >= G.size() || ny >= G[0].size() || G[nx][ny] == WALL || G[nx][ny] == VISITED)
            continue;

        //
            Diagonal Check :
            1- Up Left (-1, -1)
                - Check (-1, 0) & (0, -1)
            2- Up Right (-1, 1)
                - Check (-1, 0) & (0, 1)
            3- Down Right (1, 1)
                - Check (0, 1) & (1, 0)
            4- Down Left (1, -1)
                - Check (0, -1) & (1, 0)
        //
        if ((dr[i] == -1 && dc[i] == -1 && (G[x - 1][y] == WALL || G[x][y - 1] == WALL)) ||
            (dr[i] == -1 && dc[i] == 1 && (G[x - 1][y] == WALL || G[x][y + 1] == WALL)) ||
            (dr[i] == 1 && dc[i] == 1 && (G[x][y + 1] == WALL || G[x + 1][y] == WALL)) ||
            (dr[i] == 1 && dc[i] == -1 && (G[x][y - 1] == WALL || G[x + 1][y] == WALL)))
            continue;

        pair<int, int> current = cell.second;
        pair<int, int> next = { nx, ny };
        double new_dist = calc_distance(dist[x][y], current, next);
        double priority = new_dist + heuristic(next, end);
        if (G[nx][ny] == PATH)
        {
            frontier.push({ -priority, next });
            G[nx][ny] = PENDING;
            parent[nx][ny] = cell.second;
            dist[nx][ny] = new_dist;
        }
        if (G[nx][ny] == PENDING)
        {
            if (new_dist < dist[nx][ny])
            {
                frontier.push({ -priority, next });
                parent[nx][ny] = cell.second;
                dist[nx][ny] = new_dist;
            }
        }
    }
}

vector<pair<int, int>> AStar(vector<vector<CellState>>& G, pair<int, int> start, pair<int, int> end)
{
    // 1- Create frontier queue, parent array, distance array(weight)
    int rows = G.size(), cols = G[0].size();
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, { -1,-1 }));
    priority_queue<pair<double, pair<int, int>>> frontier;
    vector<vector<double>> dist(rows, vector<double>(cols, numeric_limits<double>::infinity()));

    // 2- Process the start node
    parent[start.first][start.second] = { -1, -1 };
    dist[start.first][start.second] = 0;
    frontier.push({ 0, start });

    if (start == end)
        return { start };

    // Loop through all neighbours
    while (!frontier.empty())
    {
        pair<double, pair<int, int>> cell = frontier.top();
        frontier.pop();

        if (cell.second == end)
            return build_path(parent, end);

        if (-cell.first > dist[cell.second.first][cell.second.second])
            continue;

        add_neighbours(frontier, cell, end, G, dist, parent);
        G[cell.second.first][cell.second.second] = VISITED;
    }

    return {}; // no path found
}
*/