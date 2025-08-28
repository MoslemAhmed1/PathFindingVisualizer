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

	// Initializing Font & Button Textures
	icons[BFS_BTN] = LoadTexture("assets/img/BFS.png");
	icons[DIJKSTRA_BTN] = LoadTexture("assets/img/Dijkstra.png");
	icons[ASTAR_BTN] = LoadTexture("assets/img/Astar.png");
	icons[ADD_START_BTN] = LoadTexture("assets/img/SetStart.png");
	icons[ADD_END_BTN] = LoadTexture("assets/img/SetEnd.png");
	icons[ADD_WALL_BTN] = LoadTexture("assets/img/SetWall.png");
	icons[CLEAR_GRID_BTN] = LoadTexture("assets/img/ClearGrid.png");

	// Load Font
	font = LoadFont("assets/fonts/Verdana-Bold.ttf");
	if (!IsFontValid(font)) 
	{
		cout << "Warning: Failed to load Verdana font, using default font." << endl;
		font = GetFontDefault(); // Raylib's default font
	}
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
	float barHeight = UI.StatusBarHeight;
	float barWidth = UI.StatusBarWidth;
	float barX = (UI.width - barWidth) / 2.0f; // Center horizontally = 200
	
	// Center Vertically = 80 + 30 + 400 = 510 --> 600 - 510 = 90 - 40 = 50 / 2 = 25
	float gridBottom = UI.ToolBarHeight + UI.TopMargin + UI.GridHeight; // 510
	float availableSpace = UI.height - gridBottom; // 90
	float barY = gridBottom + (availableSpace - barHeight) / 2; // 510 + 25 = 535

	// Status bar background
	DrawRectangleRounded({ (barX - 5.0f), (barY - 5.0f), (barWidth + 10.0f), (barHeight + 10.0f) }, 0.2f, 10, BLUE);
	DrawRectangleRounded({ barX, barY, barWidth, barHeight }, 0.2f, 10, UI.StatusBarColor);
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
		Rectangle bounds = buttons[i]->buttonBounds;
		ButtonType type = buttons[i]->buttonType;

		Texture2D icon = icons[type];
		Vector2 iconPos = { bounds.x + (bounds.width - icon.width) / 2,
						   bounds.y + (bounds.height - icon.height) / 2 };

		DrawTextureEx(icon, iconPos, 0.0f, 1.0f, WHITE);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	// First clear the status bar from any previous writing

	float gridBottom = UI.ToolBarHeight + UI.TopMargin + UI.GridHeight;
	float availableSpace = UI.height - gridBottom;

	float statusBarX = (UI.width - UI.StatusBarWidth) / 2.0f;
	float statusBarY = gridBottom + (availableSpace - UI.StatusBarHeight) / 2;

	float posX = statusBarX + 10.0f;
	float posY = statusBarY + (UI.StatusBarHeight / 2.0f - UI.MsgFontSize / 2.0f);

	DrawTextEx(font, msg.c_str(), {posX, posY}, UI.MsgFontSize, 1.0f, UI.MsgColor);
	
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
	int gap = UI.CellGap;
	float drawSize = baseSize - gap;

	// Adjust starting position to center the cell with gap
	float drawX = cellStartX + gap / 2.0;
	float drawY = cellStartY + gap / 2.0;

	Color cellColor = UI.CellColor_Path;

	// Shadow
	DrawRectangleRounded({ drawX + 2, drawY + 2, drawSize, drawSize }, 0.2f, 6, Fade(BLACK, 0.3f));

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

	Rectangle rect = { drawX, drawY, drawSize, drawSize };
	DrawRectangleRounded(rect, 0.2f, 6, cellColor);
	DrawRectangleRoundedLines(rect, 0.2f, 6, BLACK);
}

//////////////////////////////////////////////////////////////////////////////////////////

Output::~Output()
{
	for (int i = 0; i < 7; i++)
	{
		UnloadTexture(icons[i]);
	}

	UnloadFont(font);
}
