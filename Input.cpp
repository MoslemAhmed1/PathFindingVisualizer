#include "Input.h"

#include "Output.h"

//======================================================================================//
//								General Functions									    //
//======================================================================================//

/*
Input::Input(window* pW)
{
	pWind = pW; // point to the passed window
}
*/
////////////////////////////////////////////////////////////////////////////////////////// 

void Input::GetPointClicked(int& x, int& y) const
{
	x = GetMouseX();
	y = GetMouseY();
}

//======================================================================================//
//								Program  Functions								        //
//======================================================================================//
/*
ActionType Input::GetUserAction() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	//  ============ GUI in the Design mode ============
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// [1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_ADD_LADDER: return ADD_LADDER;
			case ITM_ADD_SNAKE: return ADD_SNAKE;
			case ITM_ADD_CARD: return ADD_CARD;

				///TODO: Add cases for the other items of Design Mode
			case ITM_COPY_CARD: return COPY_CARD;						// NEW
			case ITM_CUT_CARD: return CUT_CARD;							// NEW
			case ITM_PASTE_CARD: return PASTE_CARD;						// NEW
			case ITM_EDIT_CARD: return EDIT_CARD;						// NEW
			case ITM_DELETE_GAME_OBJECT: return DELETE_GAME_OBJECT;		// NEW
			case ITM_SAVE_GRID: return SAVE_GRID;						// NEW
			case ITM_OPEN_GRID: return OPEN_GRID;						// NEW

			case ITM_EXIT: return EXIT;
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;

			default: return EMPTY;	// A click on empty place in toolbar
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

	// ============ GUI in the Play mode ============
	else
	{
		///TODO:
		// perform checks similar to Design mode checks above for the Play Mode
		// and return the corresponding ActionType

		// NEW : See the Design Mode Checks to Understand Each Check
		if (y >= 0 && y < UI.ToolBarHeight)
		{

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
			case ITM_ROLL_DICE: return ROLL_DICE;
			case ITM_INPUT_DICE_VALUE: return INPUT_DICE_VALUE;
			case ITM_NEW_GAME: return NEW_GAME;
			case ITM_EXIT_TWO: return EXIT_TWO;
			case ITM_SWITCH_TO_DESIGN_MODE: return TO_DESIGN_MODE;

			default: return EMPTY;
			}

		}

		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		return STATUS;

	}

}
*/
////////////////////////////////////////////////////////////////////////////////////////// 
/*
CellPosition Input::GetCellClicked() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	// Get the coordinates of the user click

	CellPosition cellPos;

	if (UI.InterfaceMode == MODE_DESIGN)
	{
		if (y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
		{
			///TODO: SetHCell and SetVCell of the object cellPost appropriately
			//       using the coordinates x, y and the appropriate variables of the UI_Info Object (UI)

			cellPos.SetHCell(x / UI.CellWidth);
			cellPos.SetVCell((y / UI.CellHeight) - 1);

		}
		// New If Click Not on a Cell
		else
		{
			cellPos.SetHCell(-1);
			cellPos.SetVCell(-1);
		}
	}

	return cellPos;
}
*/
////////////////////////////////////////////////////////////////////////////////////////// 