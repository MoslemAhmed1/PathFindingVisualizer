#include "Input.h"

#include "Output.h"

//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(vector<Button*>& buttons) : buttons(buttons)
{

}

void Input::GetPointClicked(int& x, int& y) const 
{
	while (!WindowShouldClose()) 
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
		{
			x = GetMouseX();
			y = GetMouseY();
			return;
		}

		// Yield to prevent CPU hogging
		WaitTime(0.01); // Small delay to avoid busy-waiting
	}
}

//======================================================================================//
//								Program  Functions								        //
//======================================================================================//

ActionType Input::GetUserAction() const
{
	int x, y;
	GetPointClicked(x, y);
	cout << "X: " << x << ", Y: " << y << endl;
	Vector2 mousePos = { (float)x, (float)y };
	ButtonType type = NONE;

	// [1] If user clicks on the Toolbar
	if (y >= 0 && y < UI.ToolBarHeight)
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			if (buttons[i]->isPressed(mousePos))
				type = buttons[i]->buttonType;
		}

		switch (type)
		{
		case BFS_BTN:
			return RUN_BFS;
			break;
		case DIJKSTRA_BTN:
			return RUN_DIJKSTRA;
			break;
		case ASTAR_BTN:
			return RUN_ASTAR;
			break;
		case ADD_WALL_BTN:
			return ADD_WALL;
			break;
		case ADD_START_BTN:
			return ADD_START;
			break;
		case ADD_END_BTN:
			return ADD_END;
			break;
		case CLEAR_GRID_BTN:
			return CLEAR_GRID;
			break;
		case GREEDY_BFS_BTN:
			return RUN_GREEDY_BFS;
			break;
		default:
			return EMPTY;
			break;
		}
	}

	// [2] User clicks on the grid area
	if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
	{
		return GRID_AREA;
	}

	// [3] User clicks on the status bar
	return STATUS;

}

////////////////////////////////////////////////////////////////////////////////////////// 

CellPosition Input::GetCellClicked() const
{
	int x, y;
	GetPointClicked(x, y);
	cout << "X: " << x << ", Y: " << y << endl;
	CellPosition cellPos;

	if ((y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight)) && (x >= UI.LeftMargin && x <= (UI.width - UI.LeftMargin)))
	{
		cellPos.SetHCell((x - UI.LeftMargin) / UI.CellSize);
		cellPos.SetVCell((y - UI.TopMargin - UI.ToolBarHeight) / UI.CellSize);

	}
	// If Click Not on a Cell
	else
	{
		cellPos.SetHCell(-1);
		cellPos.SetVCell(-1);
	}

	return cellPos;
}

CellPosition Input::GetCellClicked_F() const
{
	int x = GetMouseX(); // Get current mouse position (no waiting)
	int y = GetMouseY(); // Get current mouse position
	CellPosition cellPos;

	if ((y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight)) && (x >= UI.LeftMargin && x <= (UI.width - UI.LeftMargin)))
	{
		cellPos.SetHCell((x - UI.LeftMargin) / UI.CellSize);
		cellPos.SetVCell((y - UI.TopMargin - UI.ToolBarHeight) / UI.CellSize);

	}
	// If Click Not on a Cell
	else
	{
		cellPos.SetHCell(-1);
		cellPos.SetVCell(-1);
	}

	return cellPos;
}

////////////////////////////////////////////////////////////////////////////////////////// 