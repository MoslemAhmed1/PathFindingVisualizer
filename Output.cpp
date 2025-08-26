#include "Output.h"

#include "Input.h"

////////////////////////////////////////////////////////////////////////////////////////// 

Output::Output()
{

	// Widths and Heights

	UI.StatusBarHeight = 60;
	UI.ToolBarHeight = 80;
	UI.ButtonWidth = 120; // To be changed
	UI.ButtonHeight = 40; // To be changed

	UI.width = 1000;
	UI.height = 600;

	UI.LeftMargin = 200;
	UI.TopMargin = 30;

	UI.CellSize = 20;

	// Pen Colors of messages of status bar and players' info
	UI.MsgColor = RED; 
	UI.MsgFontSize = 18;

	// Background Colors of toolbar and statusbar 
	UI.ToolBarColor = WHITE;
	UI.StatusBarColor = LIGHTGRAY;

	// Line Colors of the borders of each cell
	UI.GridLineColor = RAYWHITE;
	UI.CellColor_Path = { 161, 166, 163, 255 };
	UI.CellColor_Wall = BLACK;
	UI.CellColor_Pending = SKYBLUE;
	UI.CellColor_Visited = BLUE;
	UI.CellColor_Start = GREEN;
	UI.CellColor_End = RED;
	UI.CellColor_Final = MAGENTA;

	UI.ButtonColor = LIGHTGRAY;


	// Create the output window
	InitWindow(UI.width, UI.height, "PathFinder Visualizer");
	SetTargetFPS(60);

	// Create the toolbar, grid area and status bar
	CreateToolBar();
	ClearGridArea();
	ClearStatusBar();
}

////////////////////////////////////////////////////////////////////////////////////////// 

Input* Output::CreateInput() const
{
	// The Input Object is created inside the Output class
	Input* pIn = new Input();
	return pIn;
}

//======================================================================================//
//								Some Utility Functions									//
//======================================================================================//

int Output::GetCellStartX(const CellPosition& cellPos) const
{

	int cellStartX = (cellPos.HCell() * UI.CellSize) + UI.LeftMargin;		// We find the horizontal index of the cell, 
																			//	then multiply it by the CellWidth and so it gives 
																			//	the X - Coordinate starting from the left side of the 
																			//	window until the start of the passed cell position

	return cellStartX;
}

//////////////////////////////////////////////////////////////////////////////////////////

int Output::GetCellStartY(const CellPosition& cellPos) const
{
	int cellStartY = (cellPos.VCell() * UI.CellSize) + UI.ToolBarHeight + UI.TopMargin;

	return cellStartY; 
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearToolBar() const
{
	// Clear by drawing a rectangle filled with toolbar background color
	DrawRectangle(0, 0, UI.width, UI.ToolBarHeight, UI.ToolBarColor);
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

void Output::ClearStatusBar() const
{
	// Clear drawing a rectangle filled with statusbar background color
	DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.StatusBarHeight, UI.StatusBarColor);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearGridArea() const
{
	// Draw each cell in the Grid: ( NumVerticalCells * NumberHorizontalCells )
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			CellPosition cellPos(i, j);
			DrawCell(cellPos, PATH);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateToolBar(const vector<Button>& buttons) const
{
	for (int i = 0; i < buttons.size(); i++)
	{
		Rectangle rec = buttons[i].buttonBounds;
		DrawRectangleRounded(rec, 0.3f, 6, UI.ButtonColor);
		DrawText(buttons[i].buttonText, rec.x + 5, rec.y + 5, UI.MsgFontSize, UI.MsgColor);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	// First clear the status bar from any previous writing

	int posY = UI.height - UI.StatusBarHeight + (UI.StatusBarHeight / 2 - UI.MsgFontSize / 2);

	DrawText(msg.c_str(), 10, posY, UI.MsgFontSize, UI.MsgColor);
	
	//Color : UI.MsgColor
	//Font : 18, BOLD, Verdana
	//posX : 10
	//posY : UI.height - (int)(UI.StatusBarHeight / 1.3)
}

//======================================================================================//
//			         			Drawing Functions   									//
//======================================================================================//

void Output::DrawCell(const CellPosition& cellPos, CellState state) const
{	
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);
	int size = UI.CellSize;
	Color cellColor = UI.CellColor_Path;

	switch(state)
	{
	case PATH:
		cellColor = UI.CellColor_Path;
		break;
	case WALL:
		cellColor = UI.CellColor_Wall;
		break;
	case START:
		cellColor = UI.CellColor_Start;
		break;
	case END:
		cellColor = UI.CellColor_End;
		break;
	case PENDING:
		cellColor = UI.CellColor_Pending;
		break;
	case VISITED:
		cellColor = UI.CellColor_Visited;
		break;
	case FINAL_PATH:
		cellColor = UI.CellColor_Final;
		break;
	}

	Rectangle rect = { cellStartX, cellStartY, size, size };

	DrawRectangleRounded(rect, 0.2f, 6, cellColor);

}

//////////////////////////////////////////////////////////////////////////////////////////

Output::~Output()
{
}
