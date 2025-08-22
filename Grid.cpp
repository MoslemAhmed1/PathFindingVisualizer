#include "Grid.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "Astar.h"

Grid::Grid()
{
    grid.resize(NUM_VERTICAL_CELLS, vector<Cell*>(NUM_HORIZONTAL_CELLS));

	// Allocate the Cell Objects of the Grid
	for (int rows = 0; rows < NUM_VERTICAL_CELLS; rows++)
	{
		for (int cols = 0; cols < NUM_HORIZONTAL_CELLS; cols++)
		{
			grid[rows][cols] = new Cell(rows, cols);
		}
	}

    AddWalls();

    start = grid[0][0];
    end = grid[4][4];
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

void Grid::AddWalls()
{
    // add some walls
    grid[0][3]->SetCellState(WALL);
    grid[1][0]->SetCellState(WALL);
    grid[1][1]->SetCellState(WALL);
    grid[1][3]->SetCellState(WALL);
    grid[3][1]->SetCellState(WALL);
    grid[3][2]->SetCellState(WALL);
    grid[3][3]->SetCellState(WALL);
    grid[3][4]->SetCellState(WALL);
}

void Grid::SetStartCell(int r, int c)
{
    // TODO : some verifications later
    start = grid[r][c];
}

void Grid::SetEndCell(int r, int c)
{
    // TODO : some verifications later
    end = grid[r][c];
}


// ========= Setters and Getters Functions =========

/*
Input* Grid::GetInput() const
{
	return pIn;
}

Output* Grid::GetOutput() const
{
	return pOut;
}
*/

// ========= User Interface Functions =========

/*
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

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}
*/

// ===================== Additional Functions ===================== //


void Grid::ClearGrid()
{
	for (int currRow = NUM_VERTICAL_CELLS - 1; currRow > 0; currRow--)
	{
		for (int currColumn = 0; currColumn <= NUM_HORIZONTAL_CELLS; currColumn++)
		{
			
		}
	}
}


// =============================================================== //


Grid::~Grid()
{
	// Deallocate the Cell Objects of the CellList
	for (int i = 0; i < NUM_VERTICAL_CELLS; i++)
	{
		for (int j = 0; j < NUM_HORIZONTAL_CELLS; j++)
		{
			delete grid[i][j];
		}
	}
}