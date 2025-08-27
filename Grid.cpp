#include "Grid.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "Astar.h"

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

    msg = "";
}

// ========= Common Algorithm Functions =========

vector<Cell*> Grid::GetPath(ChosenAlgorithm algorithm)
{
    vector<Cell*> path;

    switch (algorithm)
    {
    case BFS_ALGORITHM:
        BFS(grid, start, end, path, pOut);
        break;
    case DIJKSTRA_ALGORITHM:
        Dijkstra(grid, start, end, path, pOut);
        break;
    case ASTAR_ALGORITHM:
        Astar(grid, start, end, path, pOut);
        break;
    }

    return path;
}

void Grid::PrintPath(ChosenAlgorithm algorithm)
{
    if (!start || !end) 
    {
        PrintMessage("Start or end not set!");
        return;
    }

    vector<Cell*> path = GetPath(algorithm);

    if (path.empty())
    {
        PrintMessage("No path found!");
        return;
    }

    // Copy of Grid
    vector<vector<Cell*>> displayGrid = grid;

    // Animate the path highlighting
    for (Cell* cell : path) {
        displayGrid[cell->GetCellPosition().VCell()][cell->GetCellPosition().HCell()]->SetCellState(FINAL_PATH);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        pOut->CreateToolBar();
        UpdateInterface(); // Redraws all cells with overrides
        pOut->ClearStatusBar();
        pOut->PrintMessage(GetMessage());
        EndDrawing();
        WaitTime(0.01);
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

    if (grid[r][c]->GetCellState() == PATH)
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

// ========= User Interface Functions =========
void Grid::UpdateInterface() const
{
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
}


// =============================================================== //


Grid::~Grid()
{
	// Deallocate the Cell Objects of the CellList
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete grid[i][j];
		}
	}
}