#include "Output.h"

#include "Input.h"

////////////////////////////////////////////////////////////////////////////////////////// 

Output::Output(vector<Button*>& buttons) : buttons(buttons)
{
	// Create the output window
	InitWindow(UI.width, UI.height, "PathFinder Visualizer");
	SetTargetFPS(60);

	// Create the toolbar, grid area and status bar
	BeginDrawing();
	ClearBackground(RAYWHITE);
	CreateToolBar();
	ClearGridArea();
	ClearStatusBar();
	EndDrawing();
}

////////////////////////////////////////////////////////////////////////////////////////// 

Input* Output::CreateInput(vector<Button*>& buttons) const
{
	// The Input Object is created inside the Output class
	Input* pIn = new Input(buttons);
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

void Output::CreateToolBar() const
{
	for (int i = 0; i < buttons.size(); i++)
	{
		Rectangle rec = buttons[i]->buttonBounds;
		DrawRectangleRounded(rec, 0.3f, 6, UI.ButtonColor);

		// Get text dimensions
		const char* text = buttons[i]->buttonText.c_str();
		Font font = GetFontDefault(); // Or load a custom font
		Vector2 textSize = MeasureTextEx(font, text, UI.MsgFontSize, 1);

		// Calculate centered position
		float textX = rec.x + (rec.width - textSize.x) / 2.0f;
		float textY = rec.y + (rec.height - textSize.y) / 2.0f;

		// Draw text at centered position
		DrawTextEx(font, text, { textX, textY }, UI.MsgFontSize, 1, UI.MsgColor);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	// First clear the status bar from any previous writing

	int posY = UI.height - UI.StatusBarHeight + (UI.StatusBarHeight / 2 - UI.MsgFontSize / 2);

	Font font = GetFontDefault(); // Or load a custom font
	DrawTextEx(font, msg.c_str(), {10, (float)posY}, UI.MsgFontSize, 1, UI.MsgColor);
	
	//DrawText(msg.c_str(), 10, posY, UI.MsgFontSize, UI.MsgColor);
	
	//Color : UI.MsgColor
	//Font : 18, BOLD, Verdana
	//posX : 10
	//posY : UI.height - (int)(UI.StatusBarHeight / 1.3)
}

//======================================================================================//
//			         			Drawing Functions   									//
//======================================================================================//

void Output::DrawCell(const CellPosition& cellPos, CellState state, bool isStart, bool isEnd) const
{	
	int cellStartX = GetCellStartX(cellPos);
	int cellStartY = GetCellStartY(cellPos);
	int baseSize = UI.CellSize;
	int gap = UI.cellGap;
	int drawSize = baseSize - gap;

	// Adjust starting position to center the cell with gap
	int drawX = cellStartX + gap / 2;
	int drawY = cellStartY + gap / 2;

	Color cellColor = UI.CellColor_Path;

	// Shadow
	DrawRectangleRounded({ (float)drawX + 2, (float)drawY + 2, (float)drawSize, (float)drawSize }, 0.2f, 6, Fade(BLACK, 0.3f));

	// Override for start/end during PENDING/VISITED
	if (isStart && (state == PENDING || state == VISITED)) 
		cellColor = UI.CellColor_Start;
	else if (isEnd && (state == PENDING || state == VISITED)) 
		cellColor = UI.CellColor_End;
	else 
	{
		switch (state) 
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
	}

	Rectangle rect = { (float)drawX, (float)drawY, (float)drawSize, (float)drawSize };
	DrawRectangleRounded(rect, 0.2f, 6, cellColor);
	DrawRectangleRoundedLines(rect, 0.2f, 6, BLACK);
}

//////////////////////////////////////////////////////////////////////////////////////////

Output::~Output()
{
}
