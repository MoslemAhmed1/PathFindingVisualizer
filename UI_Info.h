#pragma once

#define NumVerticalCells 21
#define NumHorizontalCells 31

#include "raylib.h"

__declspec(selectany) // This line to prevent "redefinition error"

struct UI_Info	// User Interface Info.
{
	// Widths and Heights
	int	width = 1000, height = 600,					// Window width and height
		ToolBarHeight = 100;
	
	float ButtonWidth = 120, ButtonHeight = 40;		// Buttons width and height for FIRST ROW 
													// (second row is created manually)

	int CellSize = 20, CellGap = 2;					// Size of the cell, Gap between cells

	int GridWidth = (NumHorizontalCells * CellSize);
	int GridHeight = (NumVerticalCells * CellSize);

	// Paddings & Margins
	int LeftMargin = (width - GridWidth) / 2;		// Margin to the left of the grid
	int TopMargin = 10;								// Margin to the top of the grid

	// Status Bar Calculations
	int StatusBarHeight = 40, StatusBarWidth = 700;
	float StatusBarX = (width - StatusBarWidth) / 2.0f;					// Center Horizontally : (Window Width - StatusBarWidth) / 2 
	float StatusBarY = (ToolBarHeight + TopMargin + GridHeight) +	// Center Vertically : gridBottom + (availableSpace - barHeight) / 2
		((height - (ToolBarHeight + TopMargin + GridHeight)) - StatusBarHeight) / 2.0f;

	// Pen Colors of messages of status bar
	int MsgFontSize = 20;							// Messages font size
	Color MsgColor = { 30, 58, 138, 255 };			// Messages color

	// Colors of each cell state
	Color CellColor_Path = { 161, 166, 163, 255 };	// Cell color if PATH
	Color CellColor_Wall = BLACK;					// Cell color if WALL
	Color CellColor_Pending = SKYBLUE;				// Cell color if PENDING
	Color CellColor_Visited = BLUE;					// Cell color if VISITED
	Color CellColor_Start = GREEN;					// Cell color if Start
	Color CellColor_End = RED;						// Cell color if End
	Color CellColor_Final = MAGENTA;				// CellColor if Final Path

	// Colors of toolbar and statusbar
	Color StatusBarColor = { 237, 237, 237, 255 };       // #EDEDED
	Color StatusBarBorderColor = BLUE;
	Color ToolBarColor = { 211, 224, 234, 255 };         // #D3E0EA

} UI;