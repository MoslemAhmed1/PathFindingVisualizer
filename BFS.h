#pragma once

#include "Grid.h"

class BFS
{

public:

    BFS(vector<vector<Cell*>> grid, Cell* start, Cell* end, vector<Cell*>& path);

    vector<Cell*> BuildPath(Cell* end);

    void AddNeighbours(queue<Cell*>& frontier, Cell* cell, vector<vector<Cell*>>& G);

    vector<Cell*> ApplyAlgorithm(vector<vector<Cell*>>& G, Cell* start, Cell* end);

};


/*

Works On : Directed & Undirected Graphs
Has to start from a given Source Node

BFS(G, s)
1  for each vertex u ∈ G.V − {s}	
2      u.color = WHITE
3      u.d = infinity
4      u.π = NIL
5  s.color = GRAY
6  s.d = 0
7  s.π = NIL
8  Q = Empty
9  ENQUEUE(Q, s)
10 while Q ≠ Empty						
11     u = DEQUEUE(Q)
12     for each v ∈ G.Adj[u]                      
13         if v.color == WHITE
14             v.color = GRAY
15             v.d = u.d + 1
16             v.π = u
17             ENQUEUE(Q, v)
18     u.color = BLACK

Complexity: O(V + E)
	color: white (not-visited), gray (in Q), and black (visited).
	d: distance from root (node s)
	𝜋: parent in the constructed BFS tree



======== PYTHON ========
// Method
frontier = Queue()
frontier.put(start )
came_from = dict()
came_from[start] = None

while not frontier.empty():
   current = frontier.get()

   if current == goal:
	  break

   for next in graph.neighbors(current):
	  if next not in came_from:
		 frontier.put(next)
		 came_from[next] = current

// Backtracking to get the path
current = goal
path = []
while current != start:
   path.append(current)
   current = came_from[current]
path.append(start) # optional
path.reverse() # optional

*/

// BFS OOP

/*

void add_neighbours(priority_queue<Cell*>& frontier, Cell* cell, vector<vector<Cell*>>& G)
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
        }
    }
}

vector<Cell*> bfs(vector<vector<Cell*>>& G, Cell* start, Cell* end)
{
    // 1- Create frontier queue, parent array, distance array(weight)
    int rows = G.size(), cols = G[0].size();
    priority_queue<Cell*> frontier;

    // 2- Process the start node
    frontier.push(start);
    start->SetCellState(PENDING);

    if (start == end)
        return { start };

    // Loop through all neighbours
    while (!frontier.empty())
    {

        Cell* cell = frontier.top();
        frontier.pop();


        if (cell == end)
            return build_path(start, end);


        add_neighbours(frontier, cell, G);
        cell->SetCellState(VISITED);
    }

    return {}; // no path found
}

*/


// BFS Normal

/*
void add_neighbours(queue<pair<int, int>>& frontier, vector<vector<CellState>>& G, pair<int, int> cell, vector<vector<pair<int, int>>>& parent)
{
    int x = cell.first;
    int y = cell.second;

    int dr[4] = { 0, -1, 0, 1 };
    int dc[4] = { -1, 0, 1, 0 };

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dr[i];
        int ny = y + dc[i];

        if (nx < 0 || ny < 0 || nx >= G.size() || ny >= G[0].size())
            continue;

        if (G[nx][ny] == PATH)
        {
            frontier.push({ nx, ny });
            G[nx][ny] = PENDING;
            parent[nx][ny] = cell;
        }
    }
}

vector<pair<int, int>> BFS(vector<vector<CellState>>& G, pair<int, int> start, pair<int, int> end)
{
    int n = G.size(), m = G[0].size();
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, { -1,-1 }));
    queue<pair<int, int>> frontier;

    parent[start.first][start.second] = { -1, -1 };
    frontier.push(start);
    G[start.first][start.second] = PENDING;

    if (start == end)
        return { start };

    while (!frontier.empty())
    {
        // 1- Create frontier Queue and parent array
        pair<int, int> cell = frontier.front();
        frontier.pop();

        // 2- Push the start node (assume start node != end node)
        if (cell == end)
            return build_path(parent, end);

        // Loop through all neighbours
        add_neighbours(frontier, G, cell, parent);
        G[cell.first][cell.second] = VISITED;
    }

    return {}; // no path found
}
*/


// Common Functions 

/*

vector<Cell*> build_path(Cell* start, Cell* end)
{
    vector<Cell*> path;

    for (Cell* cur = end; cur != nullptr; cur = cur->GetParentCell())
    {
        path.push_back(cur);
    }

    reverse(path.begin(), path.end());
    return path;
}

void printPath(const vector<vector<Cell*>>& grid, const vector<Cell*>& path, Cell* start, Cell* end)
{
    // Copy of Grid
    vector<vector<Cell*>> displayGrid = grid;

    // Mark the path cells
    for (Cell* cell : path)
    {
        displayGrid[cell->GetCellPosition().VCell()][cell->GetCellPosition().HCell()]->SetCellState(FINAL_PATH);
    }

    // Print the grid with symbols
    for (int r = 0; r < displayGrid.size(); r++)
    {
        for (int c = 0; c < displayGrid[r].size(); c++)
        {
            if (grid[r][c]->GetCellState() == WALL)
            {
                cout << "# ";
            }
            else if (start->GetCellPosition().VCell() == r && start->GetCellPosition().HCell() == c)
            {
                cout << "S ";
            }
            else if (end->GetCellPosition().VCell() == r && end->GetCellPosition().HCell() == c)
            {
                cout << "E ";
            }
            else if (displayGrid[r][c]->GetCellState() == FINAL_PATH)
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

void printGrid(const vector<vector<Cell*>>& grid, Cell* start, Cell* end)
{
    for (int r = 0; r < grid.size(); r++)
    {
        for (int c = 0; c < grid[r].size(); c++)
        {
            if (start->GetCellPosition().VCell() == r && start->GetCellPosition().HCell() == c)
            {
                cout << "S ";
            }
            else if (end->GetCellPosition().VCell() == r && end->GetCellPosition().HCell() == c)
            {
                cout << "E ";
            }
            else if (grid[r][c]->GetCellState() == WALL)
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

*/