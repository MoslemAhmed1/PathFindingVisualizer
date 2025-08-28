#include "App.h"
#include "Grid.h"

App::App()
{	
	// Spacing between buttons
	int spacing = 10;
	float x = 50;
	float y = 20;

	string btn_text[7] = { "BFS", "Dijkstra", "A*", "Set Wall", "Set Start", "Set End", "Clear Grid" };
	ButtonType type[7] = { BFS_BTN, DIJKSTRA_BTN, ASTAR_BTN, ADD_WALL_BTN, ADD_START_BTN, ADD_END_BTN, CLEAR_GRID_BTN };
	
	// Initialize buttons (Error)
	for (int i = 0; i < 7; i++)
	{
		Button* button = new Button(btn_text[i], { x, y }, type[i]);
		buttons.push_back(button);
		x += (UI.ButtonWidth + spacing);
	}

	// Create Input, Output and Grid
	pOut = new Output(buttons);
	pIn = pOut->CreateInput(buttons);
	pGrid = new Grid(pIn, pOut);

	// Initialize Flags & Actions
	pendingAction = EMPTY;
	currentFlag = NO_CURRENT_FLAG;
}

////////////////////////////////////////////////////////////////////////////////////

App::~App()
{
	delete pGrid;
	delete pIn;
	delete pOut;
	for (Button* btn : buttons) 
		delete btn;
}

////////////////////////////////////////////////////////////////////////////////////

void App::Run()
{
	while (!WindowShouldClose()) 
	{
		// Render UI every frame
		BeginDrawing();
		ClearBackground(RAYWHITE);
		pOut->CreateToolBar();
		pGrid->UpdateInterface();
		pOut->ClearStatusBar();
		pOut->PrintMessage(pGrid->GetMessage());
		EndDrawing();

		// Step the algorithm if running
		if (currentFlag == ALGORITHM_RUNNING) 
		{
			pGrid->StepAlgorithm();

			if (!pGrid->IsAlgorithmRunning())
				currentFlag = NO_CURRENT_FLAG;

			WaitTime(0.01); // Control animation speed
		}

		// Handle input (only if not running algorithm, to avoid interference)
		if (currentFlag == SETTING_WALLS)
		{
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				CellPosition position = pIn->GetCellClicked_F();
				if (position.IsValidCell())
				{
					pGrid->SetWallCell(position.VCell(), position.HCell());
					WaitTime(0.01);
				}
			}

			if (IsKeyPressed(KEY_E))
			{
				currentFlag = NO_CURRENT_FLAG;
				pGrid->PrintMessage("Wall setting mode exited");
			}
		}
		else if (currentFlag != ALGORITHM_RUNNING && currentFlag != SETTING_WALLS && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (currentFlag == WAITING_FOR_CELL) 
			{
				CellPosition position = pIn->GetCellClicked();
				ExecGridAction(pendingAction, position);
				currentFlag = NO_CURRENT_FLAG;
				pendingAction = EMPTY;
			}
			else 
			{
				ActionType actType = pIn->GetUserAction();
				ExecuteAction(actType);
			}
		}
	}
	CloseWindow();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

void App::ExecuteAction(ActionType ActType)
{
	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_START:
		AddStart();
		break;

	case ADD_END:
		AddEnd();
		break;

	case ADD_WALL:
		AddWall();
		break;

	case CLEAR_GRID:
		pGrid->ClearGrid();
		break;

	case RUN_BFS:
		Run_BFS();
		break;

	case RUN_DIJKSTRA:
		Run_Dijkstra();
		break;

	case RUN_ASTAR:
		Run_AStar();
		break;

	case STATUS:
	case EMPTY:
		return;
	}
}

void App::ExecGridAction(ActionType ActType, CellPosition position)
{
	if (position.IsValidCell()) 
	{
		switch (ActType) 
		{
		case ADD_START:
			if (!pGrid->SetStartCell(position.VCell(), position.HCell())) 
			{
				pGrid->PrintMessage("There's already a start node, click on it to remove it!");
			}
			break;
		case ADD_END:
			if (!pGrid->SetEndCell(position.VCell(), position.HCell())) 
			{
				pGrid->PrintMessage("There's already an end node, click on it to remove it!");
			}
			break;
		case ADD_WALL:
			if (!pGrid->SetWallCell(position.VCell(), position.HCell())) 
			{
				pGrid->PrintMessage("Can't select start/end nodes!");
			}
			break;
		default:
			break;
		}
	}
	else 
	{
		pGrid->PrintMessage("Invalid cell clicked!");
	}
}

void App::AddStart()
{
	pGrid->PrintMessage("Click on a cell to add a start node");
	currentFlag = WAITING_FOR_CELL;
	pendingAction = ADD_START;
}

void App::AddEnd()
{
	pGrid->PrintMessage("Click on a cell to add an end node");
	currentFlag = WAITING_FOR_CELL;
	pendingAction = ADD_END;
}

void App::AddWall()
{
	pGrid->PrintMessage("Wall Setting Mode Entered. Press E to Exit the Mode");
	currentFlag = SETTING_WALLS;
	pendingAction = ADD_WALL;
}

void App::Run_BFS()
{
	if (pGrid->GetStartCell() && pGrid->GetEndCell()) 
	{
		pGrid->ClearPath();
		pGrid->GetPath(BFS_ALGORITHM);
		currentFlag = ALGORITHM_RUNNING;
		pGrid->PrintMessage("Running BFS Algorithm...");
	}
	else 
	{
		pGrid->PrintMessage("Set start and end points first!");
	}
}

void App::Run_Dijkstra()
{
	if (pGrid->GetStartCell() && pGrid->GetEndCell())
	{
		pGrid->ClearPath();
		pGrid->GetPath(DIJKSTRA_ALGORITHM);
		currentFlag = ALGORITHM_RUNNING;
		pGrid->PrintMessage("Running Dijkstra Algorithm...");
	}
	else 
	{
		pGrid->PrintMessage("Set start and end points first!");
	}
}

void App::Run_AStar()
{
	if (pGrid->GetStartCell() && pGrid->GetEndCell())
	{
		pGrid->ClearPath();
		pGrid->GetPath(ASTAR_ALGORITHM);
		currentFlag = ALGORITHM_RUNNING;
		pGrid->PrintMessage("Running A* Algorithm...");
	}
	else 
	{
		pGrid->PrintMessage("Set start and end points first!");
	}
}