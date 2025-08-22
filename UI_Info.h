#pragma once

#define NUM_VERTICAL_CELLS 5
#define NUM_HORIZONTAL_CELLS 5

#include "raylib.h"

enum GUI_MODE		// Graphical user interface mode
{
	MODE_DESIGN,	// Design mode (startup mode)
	MODE_RUN        // Run Algorithm mode
};

__declspec(selectany) // This line to prevent "redefinition error"

struct UI_Info	// User Interface Info.
{
	GUI_MODE InterfaceMode;

	int	width, height,			// Window width and height
		wx, wy,					// Window starting coordinates
		StatusBarHeight,		// Status Bar Height
		ToolBarHeight,			// Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;			// Width of each item in toolbar menu

	int CellHeight;				// Height of 1 CELL
	int CellWidth;				// Width of 1 CELL

	Color MsgColor;				// Messages color (usually used in statusbar)

	Color CellColor_Path;		// Cell color if PATH
	Color CellColor_Wall;		// Cell color if WALL
	Color CellColor_Pending;	// Cell color if PENDING
	Color CellColor_Visited;	// Cell color if VISITED
	Color CellColor_Start;		// Cell color if Start
	Color CellColor_End;		// Cell color if End

	Color ToolBarColor;			// Toolbar color (toolbar background)
	Color StatusBarColor;		// Statusbar color (statusbar background)

	Color GridLineColor;		// Color of the Lines separating adjacent cells

} UI;	// create a global object UI