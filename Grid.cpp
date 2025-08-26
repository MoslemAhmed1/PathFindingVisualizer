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

    // Mark the path cells
    for (Cell* cell : path)
    {
        displayGrid[cell->GetCellPosition().VCell()][cell->GetCellPosition().HCell()]->SetCellState(FINAL_PATH);
        pOut->DrawCell(cell->GetCellPosition(), VISITED); // Draw visited cell
        EndDrawing();
        WaitTime(0.01); // 10ms delay for visualization
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

// ========= User Interface Functions =========
void Grid::UpdateInterface() const
{
    for (int row = 0; row < NumVerticalCells; row++)
    {
        for (int col = 0; col < NumHorizontalCells; col++)
        {
            grid[row][col]->DrawCell(pOut);
        }
    }
}


void Grid::PrintMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
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