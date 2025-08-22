#include "raylib.h"
#include "ApplicationManager.h"
#include "Grid.h"
using namespace std;

int main(int argc, char* argv)
{

    Grid grid;

    cout << "GRID\n";
    grid.PrintGrid();
    cout << "PATH\n";
    grid.PrintPath(ASTAR_ALGORITHM);

    // auto path = grid.GetPath(BFS_ALGORITHM);

/*
    if (path.empty())
    {
        cout << "No path found\n";
        return 0;
    }
    else
    {
        cout << "Path found:\n";
        for (auto cell : path) {
            cout << "(" << cell->GetCellPosition().VCell() << "," << cell->GetCellPosition().HCell() << ") ";
        }
        cout << "\n";
    }
*/
   
    return 0;

}


/*
int main()
{
    ActionType ActType;

    ApplicationManager AppManager;

    // Initialize window
    InitWindow(800, 600, "Raylib Test");

    // Main Loop
    do
    {

        BeginDrawing();
        ClearBackground(BLUE);
        EndDrawing();

        //Read user action
        ActType = AppManager.GetUserAction();

        //Exexute the action
        AppManager.ExecuteAction(ActType);

        //Update the drawings of the window after executing the action
        AppManager.UpdateInterface();

    } while (!WindowShouldClose());
    
    return 0;
}
*/


/*
Outline (later) :

// Grid
        // Cells
            // Type
                // Path
                // Wall
            // Status (might just save the coordinates from the input instead of the attribute)
                // Start
                // End
            // Color
                // Not Visited : Gray
                // Pending : Brown Gray
                // Visited : Blue
                // Start : Green
                // End : Red

// Buttons
    - Start
    - End
    - Wall
    - Clear
    - 3 Buttons : BFS / Dijkstra / AStar
*/

