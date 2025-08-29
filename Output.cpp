#include "Output.h"

#include "Input.h"

//////////////////////////////////////////////////////////////////////////////////////////

Output::Output(vector<Button*>& buttons) : buttons(buttons)
{
	// Create & Initialize the output window
	InitWindow(UI.width, UI.height, "PathFinder Visualizer");
	SetTargetFPS(60);

	// Create the toolbar, grid area and status bar
	BeginDrawing();
	ClearBackground(RAYWHITE);
	CreateToolBar();
	ClearGridArea();
	ClearStatusBar();
	EndDrawing();

	// Initializing Button Textures (First Row)
	icons[BFS_BTN] = LoadTexture("assets/img/BFS.png");
	icons[DIJKSTRA_BTN] = LoadTexture("assets/img/Dijkstra.png");
	icons[ASTAR_BTN] = LoadTexture("assets/img/Astar.png");
	icons[ADD_START_BTN] = LoadTexture("assets/img/SetStart.png");
	icons[ADD_END_BTN] = LoadTexture("assets/img/SetEnd.png");
	icons[ADD_WALL_BTN] = LoadTexture("assets/img/SetWall.png");
	icons[CLEAR_GRID_BTN] = LoadTexture("assets/img/ClearGrid.png");

	// Initializing Button Textures (Second Row)
	icons[GREEDY_BFS_BTN] = LoadTexture("assets/img/GBFS.png");
	icons[GENERATE_MAZE_BTN] = LoadTexture("assets/img/GenMaze.png");

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
	Input* pIn = new Input(buttons);
	return pIn;
}

//======================================================================================//
//								Some Utility Functions									//
//======================================================================================//

int Output::GetCellStartX(const CellPosition& cellPos) const
{
	int cellStartX = (cellPos.HCell() * UI.CellSize) + UI.LeftMargin;		

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
	// Status bar background + border
	Rectangle border = { (UI.StatusBarX - 5.0f), (UI.StatusBarY - 5.0f), (UI.StatusBarWidth + 10.0f), (UI.StatusBarHeight + 10.0f) };
	Rectangle bar = { UI.StatusBarX, UI.StatusBarY, (float)UI.StatusBarWidth, (float)UI.StatusBarHeight };
	DrawRectangleRounded(border, 0.2f, 10, BLUE);
	DrawRectangleRounded(bar, 0.2f, 10, UI.StatusBarColor);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearGridArea() const
{
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
	Vector2 mousePos = GetMousePosition();
	bool hovered = false;

	for (int i = 0; i < buttons.size(); i++)
	{
		Rectangle bounds = buttons[i]->buttonBounds;
		ButtonType type = buttons[i]->buttonType;

		bool isHovered = CheckCollisionPointRec(mousePos, bounds);

		Texture2D icon = icons[type];
		Vector2 iconPos = { bounds.x + (bounds.width - icon.width) / 2,
						   bounds.y + (bounds.height - icon.height) / 2 };

		if (isHovered)
		{
			hovered = true;
			// Shift scaled buttons back to prevent drawing them on other buttons
			iconPos.x = iconPos.x - (0.05f * bounds.width)/2;
			iconPos.y = iconPos.y - (0.05f * bounds.height)/2;
			DrawTextureEx(icon, iconPos, 0.0f, 1.05f, Fade(WHITE, 0.9f));
		}
		else
		{
			DrawTextureEx(icon, iconPos, 0.0f, 1.0f, WHITE);
		}
	}		

	// Checks hovered to change mouse cursor :)
	if(hovered)
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	else
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	
{
	ClearStatusBar();	// First clear the status bar from any previous writing

	float posX = UI.StatusBarX + 10.0f;
	float posY = UI.StatusBarY + (UI.StatusBarHeight / 2.0f - UI.MsgFontSize / 2.0f);

	DrawTextEx(font, msg.c_str(), {posX, posY}, UI.MsgFontSize, 1.0f, UI.MsgColor);
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
	float drawSize = (float) baseSize - gap;

	// Adjust starting position to center the cell with gap
	float drawX = cellStartX + gap / 2.0f;
	float drawY = cellStartY + gap / 2.0f;

	Color cellColor = UI.CellColor_Path;

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

	// Shadow
	DrawRectangleRounded({ drawX + 2, drawY + 2, drawSize, drawSize }, 0.2f, 6, Fade(BLACK, 0.3f));

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
