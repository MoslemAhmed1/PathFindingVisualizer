#include "GreedyBFS.h"

GreedyBFS::GreedyBFS(vector<vector<Cell*>>& grid, Cell* start, Cell* end) : G(grid), start(start), end(end)
{
    for (int i = 0; i < NumVerticalCells; i++)
        for (int j = 0; j < NumHorizontalCells; j++)
            oldCost[i][j] = 1e9;
}

void GreedyBFS::Init()
{
    if (!start || !end)
        return;
    start->SetTotalCost(0);
    start->SetCellState(PENDING);
    frontier.push(start);
}

bool GreedyBFS::Step()
{
    if (frontier.empty())
        return true;

    Cell* cell = frontier.top();
    frontier.pop();

    if (cell->GetTotalCost() > oldCost[cell->GetCellPosition().VCell()][cell->GetCellPosition().HCell()])
        return false;

    if (cell == end)
    {
        path = BuildPath(end);
        return true;
    }

    AddNeighbours(cell);
    cell->SetCellState(VISITED);
    return false;
}

vector<Cell*> GreedyBFS::GetPath() const
{
    return path;
}

vector<Cell*> GreedyBFS::BuildPath(Cell* end)
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

double GreedyBFS::heuristic(Cell* next, Cell* end)
{
    CellPosition nextP = next->GetCellPosition();
    CellPosition endP = end->GetCellPosition();
    double dx = abs(endP.VCell() - nextP.VCell());
    double dy = abs(endP.HCell() - nextP.HCell());
    return dx + dy; // Manhattan Distance for 4 direction movement

    // return (dx + dy) + (sqrt(2) - 2) * min(dx, dy); // Octile Distance for 8-direction movement
    // return max(dx, dy) + (sqrt(2) - 1) * min (dx, dy); // Recommended for 8-direction movement
    // return sqrt(pow(dx, 2) + pow(dy, 2)); // Eucledian Distance
}

void GreedyBFS::AddNeighbours(Cell* cell)
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
        CellPosition nextPos = next->GetCellPosition();
        double priority = heuristic(next, end);

        bool isEnd = (next->GetCellState() == END);
        if (next->GetCellState() == PATH || isEnd)
        {
            next->SetTotalCost(priority);
            oldCost[nextPos.VCell()][nextPos.HCell()] = priority;
            next->SetParentCell(cell);
            G[nx][ny]->SetCellState(PENDING);
            frontier.push(next);
        }
    }
}
