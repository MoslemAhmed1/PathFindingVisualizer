#pragma once
#include "Grid.h"

class Dijkstra
{

public:
    
    Dijkstra(vector<vector<Cell*>> grid, Cell* start, Cell* end, vector<Cell*>& path);

    vector<Cell*> BuildPath(Cell* end);

    double CalcDistance(double curr_distance, Cell* curr, Cell* next);

    void AddNeighbours(priority_queue<Cell*>& frontier, Cell* cell, vector<vector<Cell*>>& G);

    vector<Cell*> ApplyAlgorithm(vector<vector<Cell*>>& G, Cell* start, Cell* end);

};


/*

Works only with positive edges.
Has to start from a given Source Node

INITIALIZE-SINGLE-SOURCE(G, s)
1  for each vertex v ? G.V
2	   v.d = infinity
3	   v.? = NIL
4  s.d = 0

DIJKSTRA(G, w, s)
1  INITIALIZE-SINGLE-SOURCE(G, s)
2  S = Empty // Empty Set
3  Q = G.V
4  while Q != Empty
5      u = EXTRACT-MIN(Q)
6      S = S U {u}
7      for each vertex v belongs to G.Adj[u]
8          RELAX(u, v, w)

w : weight of the edge

*/

// Dijkstra OOP

/*

double calc_distance(double curr_distance, Cell* curr, Cell* next)
{
    CellPosition currP = curr->GetCellPosition();
    CellPosition nextP = next->GetCellPosition();
    if ((currP.HCell() == nextP.HCell()) || (currP.VCell() == nextP.VCell()))
        return curr_distance + 1;
    else
        return curr_distance + sqrt(2);
}

void add_neighbours(priority_queue<Cell*>& frontier, Cell* cell, vector<vector<Cell*>>& G)
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
        double newCost = cell->GetTotalCost() + 1;

        if (G[nx][ny]->GetCellState() == PATH)
        {
            frontier.push(next);
            G[nx][ny]->SetCellState(PENDING);
            next->SetParentCell(current);
            next->SetTotalCost(newCost);
        }
        if (G[nx][ny]->GetCellState() == PENDING)
        {
            if (newCost < next->GetTotalCost())
            {
                frontier.push(next);
                next->SetParentCell(current);
                next->SetTotalCost(newCost);
            }
        }
    }
}

vector<Cell*> dijkstra(vector<vector<Cell*>>& G, Cell* start, Cell* end)
{
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
            return build_path(start, end);

        if (cell->GetTotalCost() > G[cell->GetCellPosition().VCell()][cell->GetCellPosition().HCell()]->GetTotalCost())
            continue;

        add_neighbours(frontier, cell, G);
        cell->SetCellState(VISITED);
    }

    return {}; // no path found
}

*/



// Dijkstra Normal

/*
#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <queue> 
#include <cmath> 
using namespace std; 
enum CellState { 
    PATH, 
    WALL, 
    PENDING, 
    VISITED, 
    FINAL_PATH 
}; 

vector<pair<int, int>> build_path(vector<vector<pair<int, int>>>& parent, pair<int, int> end) 
{ 
    vector<pair<int, int>> path; 
    
    for (pair<int, int> cur = end; cur != make_pair(-1, -1); cur = parent[cur.first][cur.second]) 
    { 
        path.push_back(cur); 
    } 
    
    reverse(path.begin(), path.end()); 
    return path; 
}

double calc_distance(double curr_distance, pair<int, int> curr, pair<int, int> next)
{
    if ((curr.first == next.first) || (curr.second == next.second))
        return curr_distance + 1;
    else
        return curr_distance + sqrt(2);
}

void add_neighbours(priority_queue<pair<double, pair<int, int>>>& frontier, pair<int, pair<int, int>> cell, vector<vector<CellState>>& G, vector<vector<double>>& dist, vector<vector<pair<int, int>>>& parent)
{
    int x = cell.second.first;
    int y = cell.second.second;

    int dr[8] = { 0, -1, 0, 1, -1, -1, 1, 1 };
    int dc[8] = { -1, 0, 1, 0, -1, 1, -1, 1 };

    for (int i = 0; i < 8; i++)
    {
        int nx = x + dr[i];
        int ny = y + dc[i];

        if (nx < 0 || ny < 0 || nx >= G.size() || ny >= G[0].size() || G[nx][ny] == WALL)
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
if ((dr[i] == -1 && dc[i] == -1 && (G[x - 1][y] == WALL && G[x][y - 1] == WALL)) ||
    (dr[i] == -1 && dc[i] == 1 && (G[x - 1][y] == WALL && G[x][y + 1] == WALL)) ||
    (dr[i] == 1 && dc[i] == 1 && (G[x][y + 1] == WALL && G[x + 1][y] == WALL)) ||
    (dr[i] == 1 && dc[i] == -1 && (G[x][y - 1] == WALL && G[x + 1][y] == WALL)))
    continue;

pair<int, int> current = cell.second;
pair<int, int> next = { nx, ny };
double new_dist = calc_distance(cell.first, current, next);

if (G[nx][ny] == PATH)
{
    frontier.push({ -new_dist, next });
    G[nx][ny] = PENDING;
    parent[nx][ny] = cell.second;
    dist[nx][ny] = new_dist;
}
if (G[nx][ny] == PENDING)
{
    if (new_dist < dist[nx][ny])
    {
        frontier.push({ -new_dist, next });
        parent[nx][ny] = cell.second;
        dist[nx][ny] = new_dist;
    }
}
    }
}

vector<pair<int, int>> dijkstra(vector<vector<CellState>>& G, pair<int, int> start, pair<int, int> end)
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

        add_neighbours(frontier, cell, G, dist, parent);
        G[cell.second.first][cell.second.second] = VISITED;
    }

    return {}; // no path found
}

void printPath(const vector<vector<CellState>>& grid, const vector<pair<int, int>>& path, pair<int, int> start, pair<int, int> end)
{
    // Copy of Grid
    auto displayGrid = grid;

    // Mark the path cells
    for (auto cell : path)
    {
        displayGrid[cell.first][cell.second] = FINAL_PATH;
    }

    // Print the grid with symbols
    for (int r = 0; r < displayGrid.size(); r++)
    {
        for (int c = 0; c < displayGrid[r].size(); c++)
        {
            if (grid[r][c] == WALL)
            {
                cout << "# ";
            }
            else if (make_pair(r, c) == start)
            {
                cout << "S ";
            }
            else if (make_pair(r, c) == end)
            {
                cout << "E ";
            }
            else if (displayGrid[r][c] == FINAL_PATH)
            {
                cout << "* ";
            }
            else
            {
                cout << ". ";
            }
        }
        cout << "\n";
    }
}

void printGrid(const vector<vector<CellState>>& grid, pair<int, int> start, pair<int, int> end)
{
    for (int r = 0; r < grid.size(); r++)
    {
        for (int c = 0; c < grid[r].size(); c++)
        {
            if (make_pair(r, c) == start)
            {
                cout << "S ";
            }
            else if (make_pair(r, c) == end)
            {
                cout << "E ";
            }
            else if (grid[r][c] == WALL)
            {
                cout << "# ";
            }
            else
            {
                cout << ". ";
            }
        }
        cout << "\n";
    }
}

int main()
{

    vector<vector<CellState>> grid = {
        {PATH, PATH, PATH, WALL, PATH},
        {WALL, WALL, PATH, WALL, PATH},
        {PATH, PATH, PATH, PATH, PATH},
        {PATH, WALL, WALL, WALL, WALL},
        {PATH, PATH, PATH, WALL, PATH}
    };

    pair<int, int> start = { 0,0 };
    pair<int, int> end = { 4,4 };

    auto path = dijkstra(grid, start, end);

    if (path.empty())
    {
        cout << "No path found\n";
        return 0;
    }
    else
    {
        cout << "Path found:\n";
        for (auto cell : path) {
            cout << "(" << cell.first << "," << cell.second << ") ";
        }
        cout << "\n";
    }

    cout << "GRID\n";
    printGrid(grid, start, end);
    cout << "PATH\n";
    printPath(grid, path, start, end);

    return 0;
}

*/

