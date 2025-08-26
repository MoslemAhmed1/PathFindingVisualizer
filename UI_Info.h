#pragma once

#define NumVerticalCells 15
#define NumHorizontalCells 30

#include "raylib.h"

__declspec(selectany) // This line to prevent "redefinition error"

struct UI_Info	// User Interface Info.
{

	int	width, height,			// Window width and height
		StatusBarHeight,		// Status Bar Height
		ToolBarHeight,			// Tool Bar Height (distance from top of window to bottom line of toolbar)
		ButtonWidth,
		ButtonHeight;

	int CellSize;				// Size of the cell
	int LeftMargin, TopMargin;

	
	int MsgFontSize;
	Color MsgColor;				// Messages color (usually used in statusbar)

	Color CellColor_Path;		// Cell color if PATH
	Color CellColor_Wall;		// Cell color if WALL
	Color CellColor_Pending;	// Cell color if PENDING
	Color CellColor_Visited;	// Cell color if VISITED
	Color CellColor_Start;		// Cell color if Start
	Color CellColor_End;		// Cell color if End
	Color CellColor_Final;

	Color ToolBarColor;			// Toolbar color (toolbar background)
	Color StatusBarColor;		// Statusbar color (statusbar background)

	Color ButtonColor;

	Color GridLineColor;		// Color of the Lines separating adjacent cells

} UI;	// create a global object UI