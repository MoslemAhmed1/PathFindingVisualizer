#pragma once

#define NumVerticalCells 21
#define NumHorizontalCells 31

#include "raylib.h"

__declspec(selectany) // This line to prevent "redefinition error"

struct UI_Info	// User Interface Info.
{
	// Widths and Heights
	int	width = 1000, height = 600,			// Window width and height
		StatusBarHeight = 40,		// Status Bar Height
		StatusBarWidth = 600,
		ToolBarHeight = 100;		// Tool Bar Height (distance from top of window to bottom line of toolbar)
	
	float ButtonWidth = 120;
	float ButtonHeight = 40;

	int CellSize = 20;				// Size of the cell
	int CellGap = 2;				// Gap between cells
	int GridWidth = (NumHorizontalCells * CellSize); // 600
	int GridHeight = (NumVerticalCells * CellSize); // 400
	int LeftMargin = (width - GridWidth) / 2;
	int TopMargin = 10;

	// Pen Colors of messages of status bar and players' info
	int MsgFontSize = 20;
	Color MsgColor = { 30, 58, 138, 255 };				// Messages color (usually used in statusbar)

	// Line Colors of the borders of each cell
	Color CellColor_Path = { 161, 166, 163, 255 };	// Cell color if PATH
	Color CellColor_Wall = BLACK;					// Cell color if WALL
	Color CellColor_Pending = SKYBLUE;				// Cell color if PENDING
	Color CellColor_Visited = BLUE;					// Cell color if VISITED
	Color CellColor_Start = GREEN;					// Cell color if Start
	Color CellColor_End = RED;						// Cell color if End
	Color CellColor_Final = MAGENTA;

	// Background Colors of toolbar and statusbar 
	Color BackgroundColorStart = { 240, 244, 248, 255 }; // #F0F4F8
	Color BackgroundColorEnd = { 255, 255, 255, 255 };   // #FFFFFF
	Color StatusBarColor = { 237, 237, 237, 255 };       // #EDEDED
	Color ToolBarColor = { 211, 224, 234, 255 };         // #D3E0EA

	Color ButtonColor = LIGHTGRAY;

	Color GridLineColor = RAYWHITE;		// Color of the Lines separating adjacent cells

} UI;	// create a global object UI