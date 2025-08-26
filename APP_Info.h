/*
Raylib Functions :
- Window
    // Window-related functions
    void InitWindow(int width, int height, const char *title);  // Initialize window and OpenGL context
    void CloseWindow(void);                                     // Close window and unload OpenGL context
    bool WindowShouldClose(void);                               // Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)

- Timing & FPS
    // Timing-related functions
    void SetTargetFPS(int fps);                                 // Set target FPS (maximum)
    float GetFrameTime(void);                                   // Get time in seconds for last frame drawn (delta time)
    double GetTime(void);                                       // Get elapsed time in seconds since InitWindow()
    int GetFPS(void);                                           // Get current FPS

- Buttons

- Input Functions
    // Input-related functions: keyboard
    bool IsKeyPressed(int key);                             // Check if a key has been pressed once
    bool IsKeyPressedRepeat(int key);                       // Check if a key has been pressed again
    bool IsKeyDown(int key);                                // Check if a key is being pressed
    bool IsKeyReleased(int key);                            // Check if a key has been released once
    bool IsKeyUp(int key);                                  // Check if a key is NOT being pressed
    int GetKeyPressed(void);                                // Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
    int GetCharPressed(void);                               // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
    void SetExitKey(int key);                               // Set a custom key to exit program (default is ESC)

    // Input-related functions: mouse
    bool IsMouseButtonPressed(int button);                  // Check if a mouse button has been pressed once
    bool IsMouseButtonDown(int button);                     // Check if a mouse button is being pressed
    bool IsMouseButtonReleased(int button);                 // Check if a mouse button has been released once
    bool IsMouseButtonUp(int button);                       // Check if a mouse button is NOT being pressed
    int GetMouseX(void);                                    // Get mouse position X
    int GetMouseY(void);                                    // Get mouse position Y
    Vector2 GetMousePosition(void);                         // Get mouse position XY
    Vector2 GetMouseDelta(void);                            // Get mouse delta between frames
    void SetMousePosition(int x, int y);                    // Set mouse position XY
    void SetMouseOffset(int offsetX, int offsetY);          // Set mouse offset
    void SetMouseScale(float scaleX, float scaleY);         // Set mouse scaling
    float GetMouseWheelMove(void);                          // Get mouse wheel movement for X or Y, whichever is larger
    Vector2 GetMouseWheelMoveV(void);                       // Get mouse wheel movement for both X and Y
    void SetMouseCursor(int cursor);                        // Set mouse cursor


- Draw Rectangle(for cells) --> Grid
    // Drawing-related functions
    void ClearBackground(Color color);                          // Set background color (framebuffer clear color)
    void BeginDrawing(void);                                    // Setup canvas (framebuffer) to start drawing
    void EndDrawing(void);                                      // End canvas drawing and swap buffers (double buffering)

    // Basic shapes drawing functions
    *==== Pixel ====*
    void DrawPixel(int posX, int posY, Color color);                                                   // Draw a pixel using geometry [Can be slow, use with care]
    *==== Line ====*
    void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);                // Draw a line
    *==== Circle ====*
    void DrawCircle(int centerX, int centerY, float radius, Color color);                              // Draw a color-filled circle
    void DrawCircleV(Vector2 center, float radius, Color color);                                       // Draw a color-filled circle (Vector version)
    void DrawCircleLines(int centerX, int centerY, float radius, Color color);                         // Draw circle outline
    void DrawCircleLinesV(Vector2 center, float radius, Color color);                                  // Draw circle outline (Vector version)
    *==== Rectangle ====*
    void DrawRectangle(int posX, int posY, int width, int height, Color color);                        // Draw a color-filled rectangle
    void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                  // Draw a color-filled rectangle (Vector version)
    void DrawRectangleRec(Rectangle rec, Color color);                                                 // Draw a color-filled rectangle
    void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   // Draw rectangle outline
    void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color);                            // Draw rectangle outline with extended parameters
    void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);              // Draw rectangle with rounded edges
    void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, Color color);         // Draw rectangle lines with rounded edges
    void DrawRectangleRoundedLinesEx(Rectangle rec, float roundness, int segments, float lineThick, Color color); // Draw rectangle with rounded edges outline

- Draw Text
    // Font loading/unloading functions
    Font GetFontDefault(void);                                                            // Get the default Font
    Font LoadFont(const char *fileName);                                                  // Load font from file into GPU memory (VRAM)

    // Text drawing functions
    void DrawFPS(int posX, int posY);                                                     // Draw current FPS
    void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font)
    void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters

    // Text font info functions
    void SetTextLineSpacing(int spacing);                                                 // Set vertical line spacing when drawing with line-breaks
    int MeasureText(const char *text, int fontSize);                                      // Measure string width for default font
    Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing);    // Measure string size for Font

- Structs
    struct Vector2;                // Vector2, 2 components
    struct Vector3;                // Vector3, 3 components
    struct Vector4;                // Vector4, 4 components
    struct Matrix;                 // Matrix, 4x4 components, column major, OpenGL style, right handed
    struct Color;                  // Color, 4 components, R8G8B8A8 (32bit)
    struct Rectangle;              // Rectangle, 4 components

    struct Image;                  // Image, pixel data stored in CPU memory (RAM)
    struct Font;                   // Font, font texture and GlyphInfo array data

    struct Camera2D;               // Camera2D, defines position/orientation in 2d space

    struct Shader;                 // Shader
    struct MaterialMap;            // MaterialMap
    struct Material;               // Material, includes shader and maps
    struct Mesh;                   // Mesh, vertex data and vao/vbo
    struct Model;                  // Model, meshes, materials and animation data
    struct ModelAnimation;         // ModelAnimation
    struct Transform;              // Transform, vertex transformation data
    struct BoneInfo;               // Bone, skeletal animation bone
    struct Ray;                    // Ray, ray for raycasting
    struct RayCollision;           // RayCollision, ray hit information
    struct BoundingBox;            // BoundingBox

    struct Wave;                   // Wave, audio wave data
    struct AudioStream;            // AudioStream, custom audio stream
    struct Sound;                  // Sound
    struct Music;                  // Music, audio stream, anything longer than ~10 seconds should be streamed

    struct AutomationEvent;        // Automation event
    struct AutomationEventList;    // Automation event list

- Colors
    // Custom raylib color palette for amazing visuals on WHITE background
    #define LIGHTGRAY  (Color){ 200, 200, 200, 255 }   // Light Gray
    #define GRAY       (Color){ 130, 130, 130, 255 }   // Gray
    #define DARKGRAY   (Color){ 80, 80, 80, 255 }      // Dark Gray
    #define YELLOW     (Color){ 253, 249, 0, 255 }     // Yellow
    #define GOLD       (Color){ 255, 203, 0, 255 }     // Gold
    #define ORANGE     (Color){ 255, 161, 0, 255 }     // Orange
    #define PINK       (Color){ 255, 109, 194, 255 }   // Pink
    #define RED        (Color){ 230, 41, 55, 255 }     // Red
    #define MAROON     (Color){ 190, 33, 55, 255 }     // Maroon
    #define GREEN      (Color){ 0, 228, 48, 255 }      // Green
    #define LIME       (Color){ 0, 158, 47, 255 }      // Lime
    #define DARKGREEN  (Color){ 0, 117, 44, 255 }      // Dark Green
    #define SKYBLUE    (Color){ 102, 191, 255, 255 }   // Sky Blue
    #define BLUE       (Color){ 0, 121, 241, 255 }     // Blue
    #define DARKBLUE   (Color){ 0, 82, 172, 255 }      // Dark Blue
    #define PURPLE     (Color){ 200, 122, 255, 255 }   // Purple
    #define VIOLET     (Color){ 135, 60, 190, 255 }    // Violet
    #define DARKPURPLE (Color){ 112, 31, 126, 255 }    // Dark Purple
    #define BEIGE      (Color){ 211, 176, 131, 255 }   // Beige
    #define BROWN      (Color){ 127, 106, 79, 255 }    // Brown
    #define DARKBROWN  (Color){ 76, 63, 47, 255 }      // Dark Brown

    #define WHITE      (Color){ 255, 255, 255, 255 }   // White
    #define BLACK      (Color){ 0, 0, 0, 255 }         // Black
    #define BLANK      (Color){ 0, 0, 0, 0 }           // Blank (Transparent)
    #define MAGENTA    (Color){ 255, 0, 255, 255 }     // Magenta
    #define RAYWHITE   (Color){ 245, 245, 245, 255 }   // My own White (raylib logo)
*/
