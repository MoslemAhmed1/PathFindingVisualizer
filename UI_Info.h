#pragma once

#define NumVerticalCells 20
#define NumHorizontalCells 30

#include "raylib.h"

__declspec(selectany) // This line to prevent "redefinition error"
// 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1
struct UI_Info	// User Interface Info.
{
	// Widths and Heights
	int	width = 1000, height = 600,			// Window width and height
		StatusBarHeight = 60,		// Status Bar Height
		ToolBarHeight = 80,			// Tool Bar Height (distance from top of window to bottom line of toolbar)
		ButtonWidth = 120,
		ButtonHeight = 40;

	int CellSize = 20;				// Size of the cell
	int LeftMargin = 200, TopMargin = 30;

	// Pen Colors of messages of status bar and players' info
	int MsgFontSize = 18;
	Color MsgColor = RED;				// Messages color (usually used in statusbar)

	// Line Colors of the borders of each cell
	Color CellColor_Path = { 161, 166, 163, 255 };	// Cell color if PATH
	Color CellColor_Wall = BLACK;					// Cell color if WALL
	Color CellColor_Pending = SKYBLUE;				// Cell color if PENDING
	Color CellColor_Visited = BLUE;					// Cell color if VISITED
	Color CellColor_Start = GREEN;					// Cell color if Start
	Color CellColor_End = RED;						// Cell color if End
	Color CellColor_Final = MAGENTA;

	// Background Colors of toolbar and statusbar 
	Color ToolBarColor = YELLOW;			// Toolbar color (toolbar background)
	Color StatusBarColor = LIGHTGRAY;		// Statusbar color (statusbar background)

	Color ButtonColor = LIGHTGRAY;

	Color GridLineColor = RAYWHITE;		// Color of the Lines separating adjacent cells

} UI;	// create a global object UI