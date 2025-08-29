#include "Grid.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "Astar.h"
#include "GreedyBFS.h"
#include "DFS.h"
#include "Prim.h"

Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
    grid.resize(NumVerticalCells, vector<Cell*>(NumHorizontalCells));

	// Allocate the Cell Objects of the Grid
	for (int rows = 0; rows < NumVerticalCells; rows++)
	{
		for (int cols = 0; cols < NumHorizontalCells; cols++)
		{
			grid[rows][cols] = new Cell(rows, cols);
		}
	}

    start = nullptr;
    end = nullptr;

    bfs = nullptr;
    dijkstra = nullptr;
    astar = nullptr;
    greedyBFS = nullptr;
    dfs = nullptr;
    prim = nullptr;
    algorithmRunning = false;
    currentAlgorithm = NO_CHOSEN_ALGORITHM;

    msg = "";
}

// ========= Common Algorithm Functions =========

void Grid::GetPath(ChosenAlgorithm algorithm) 
{
    algorithmRunning = true;
    currentAlgorithm = algorithm;
    switch (algorithm)
    {
    case BFS_ALGORITHM:
        bfs = new BFS(grid, start, end, pOut);
        bfs->Init();
        break;
    case DIJKSTRA_ALGORITHM:
        dijkstra = new Dijkstra(grid, start, end, pOut);
        dijkstra->Init();
        break;
    case ASTAR_ALGORITHM:
        astar = new Astar(grid, start, end, pOut);
        astar->Init();
        break;
    case GREEDY_BFS_ALGORITHM:
        greedyBFS = new GreedyBFS(grid, start, end, pOut);
        greedyBFS->Init();
        break;
    }
}

void Grid::StepAlgorithm() 
{
    if (!algorithmRunning) 
        return;

    bool done = false;
    switch (currentAlgorithm) 
    {
    case BFS_ALGORITHM:
        if (bfs) done = bfs->Step();
        break;
    case DIJKSTRA_ALGORITHM:
        if (dijkstra) done = dijkstra->Step();
        break;
    case ASTAR_ALGORITHM:
        if (astar) done = astar->Step();
        break;
    case GREEDY_BFS_ALGORITHM:
        if (greedyBFS) done = greedyBFS->Step();
        break;
    case GENERATE_MAZE_ALGORITHM:
        if (prim) done = prim->Step();
        else if (dfs) done = dfs->Step();
        break;
    }
    if (done) 
    {
        algorithmRunning = false;
        if (currentAlgorithm == GENERATE_MAZE_ALGORITHM)
        {
            ClearPath();
            PrintMessage("Maze Generated!");
            // if (prim) prim = nullptr;
            // if (dfs) dfs = nullptr;
            return;
        }
        PrintPath(currentAlgorithm);
    }
}

void Grid::PrintPath(ChosenAlgorithm algorithm)
{
    if (!start || !end) 
    {
        PrintMessage("Start or end not set!");
        return;
    }

    vector<Cell*> path;
    switch (currentAlgorithm)
    {
    case BFS_ALGORITHM:
        path = bfs->GetPath();
        delete bfs;
        bfs = nullptr;
        break;
    case DIJKSTRA_ALGORITHM:
        path = dijkstra->GetPath();
        delete dijkstra;
        dijkstra = nullptr;
        break;
    case ASTAR_ALGORITHM:
        path = astar->GetPath();
        delete astar;
        astar = nullptr;
        break;
    case GREEDY_BFS_ALGORITHM:
        path = greedyBFS->GetPath();
        delete greedyBFS;
        greedyBFS = nullptr;
        break;
    }

    if (path.empty())
    {
        PrintMessage("No path found!");
    }
    else
    {
        PrintMessage("Path Found!");
        for (Cell* cell : path)
        {
            if (cell == start || cell == end)
                continue;
            grid[cell->GetCellPosition().VCell()][cell->GetCellPosition().HCell()]->SetCellState(FINAL_PATH);
            BeginDrawing();
            ClearBackground(RAYWHITE);
            UpdateInterface();
            PrintMessage(msg);
            EndDrawing();
            WaitTime(0.01);
        }
    }
}

void Grid::GenerateMaze(MazeAlgorithm algorithm)
{
    // Reset previous algorithm pointers
    if (prim) {
        delete prim;
        prim = nullptr;
    }
    if (dfs) {
        delete dfs;
        dfs = nullptr;
    }

    ClearGrid();

    algorithmRunning = true;
    currentAlgorithm = GENERATE_MAZE_ALGORITHM;
    if (algorithm == PRIMS_ALGORITHM)
    {
        prim = new Prim(grid, pOut);
        prim->Init();
    }
    else if (algorithm == DFS_ALGORITHM)
    {
        dfs = new DFS(grid, pOut);
        dfs->Init();
    }
}

bool Grid::SetStartCell(int r, int c)
{
    if (r < 0 || r >= NumVerticalCells || c < 0 || c >= NumHorizontalCells)
        return false;

    if (start && grid[r][c] == start)
    {
        grid[r][c]->SetCellState(PATH);
        start = nullptr;
        return true;
    }

    if (start && start != grid[r][c])
        return false;

    if (grid[r][c]->GetCellState() == PATH)
    {
        start = grid[r][c];
        grid[r][c]->SetCellState(START);
        return true;
    }
    
    return false;
}

bool Grid::SetEndCell(int r, int c)
{
    if (end && grid[r][c] == end)
    {
        grid[r][c]->SetCellState(PATH);
        end = nullptr;
        return true;
    }

    if (end && end != grid[r][c])
        return false;

    if (!end && grid[r][c]->GetCellState() == PATH)
    {
        end = grid[r][c];
        grid[r][c]->SetCellState(END);
        return true;
    }

    return false;
}

bool Grid::SetWallCell(int r, int c)
{
    if (grid[r][c]->GetCellState() == WALL)
        grid[r][c]->SetCellState(PATH);
    else if (grid[r][c]->GetCellState() == PATH)
        grid[r][c]->SetCellState(WALL);
    else
        return false;

    return true;
}


// ========= Setters and Getters Functions =========

Input* Grid::GetInput() const
{
	return pIn;
}

Output* Grid::GetOutput() const
{
	return pOut;
}

Cell* Grid::GetStartCell() const 
{ 
    return start; 
}

Cell* Grid::GetEndCell() const 
{
    return end; 
}

string Grid::GetMessage() const
{
    return msg;
}

bool Grid::IsAlgorithmRunning() const
{
    return algorithmRunning;
}

// ========= User Interface Functions =========
void Grid::UpdateInterface() const
{
    DrawRectangleGradientV(0, 0, 1000, 600, WHITE, SKYBLUE);
    pOut->CreateToolBar();
    pOut->ClearStatusBar();

    for (int row = 0; row < NumVerticalCells; row++) 
    {
        for (int col = 0; col < NumHorizontalCells; col++) 
        {
            Cell* cell = grid[row][col];
            bool isS = (cell == start);
            bool isE = (cell == end);
            pOut->DrawCell(cell->GetCellPosition(), cell->GetCellState(), isS, isE);
        }
    }
}

void Grid::PrintMessage(string msg)
{
    this->msg = msg;
	pOut->PrintMessage(msg);
}

// ===================== Additional Functions ===================== //

void Grid::ClearGrid()
{
	for (int currRow = 0; currRow < NumVerticalCells; currRow++)
	{
		for (int currColumn = 0; currColumn < NumHorizontalCells; currColumn++)
		{
            grid[currRow][currColumn]->SetCellState(PATH);
            grid[currRow][currColumn]->SetParentCell(nullptr);
            grid[currRow][currColumn]->SetTotalCost(0);
            grid[currRow][currColumn]->Set_G_Cost(0);
            grid[currRow][currColumn]->Set_H_Cost(0);
		}
	}

    start = nullptr;
    end = nullptr;

    pOut->ClearGridArea();
    msg = "";
    pOut->ClearStatusBar();
}

void Grid::ClearPath()
{
    for (int currRow = 0; currRow < NumVerticalCells; currRow++)
    {
        for (int currColumn = 0; currColumn < NumHorizontalCells; currColumn++)
        {
            Cell* cell = grid[currRow][currColumn];
            CellState state = cell->GetCellState();
            if (state == WALL || cell == start || cell == end)
                continue;

            grid[currRow][currColumn]->SetCellState(PATH);
            grid[currRow][currColumn]->SetParentCell(nullptr);
            grid[currRow][currColumn]->SetTotalCost(0);
            grid[currRow][currColumn]->Set_G_Cost(0);
            grid[currRow][currColumn]->Set_H_Cost(0);
        }
    }

    if(start)
        start->SetCellState(START);
    if(end)
        end->SetCellState(END);

    msg = "";
    pOut->ClearStatusBar();
}


// =============================================================== //


Grid::~Grid()
{
	// Deallocate the Cell Objects of the CellList
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
            if(grid[i][j])
			    delete grid[i][j];
		}
	}

    if (bfs) delete bfs;
    if (dijkstra) delete dijkstra;
    if (astar) delete astar;
    if (greedyBFS) delete greedyBFS;
    if (dfs) delete dfs;
    if (prim) delete prim;
}