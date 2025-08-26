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
        BFS(grid, start, end, path);
        break;
    case DIJKSTRA_ALGORITHM:
        Dijkstra(grid, start, end, path);
        break;
    case ASTAR_ALGORITHM:
        Astar(grid, start, end, path);
        break;
    }

    return path;
}

void Grid::PrintPath(ChosenAlgorithm algorithm)
{
    vector<Cell*> path = GetPath(algorithm);

    if (path.empty())
    {
        cout << "No path found\n";
        return;
    }

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

void Grid::PrintGrid()
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

bool Grid::SetStartCell(int r, int c)
{
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


// ========= Setters and Getters Functions =========

Input* Grid::GetInput() const
{
	return pIn;
}

Output* Grid::GetOutput() const
{
	return pOut;
}

// ========= User Interface Functions =========

/*
* // (This is copy paste from another project, might not need it)
void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells 
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount - 1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}
*/

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


// ===================== Additional Functions ===================== //


void Grid::ClearGrid()
{
	for (int currRow = NumVerticalCells - 1; currRow > 0; currRow--)
	{
		for (int currColumn = 0; currColumn <= NumHorizontalCells; currColumn++)
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