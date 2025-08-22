#pragma once
#include "raylib.h"

class Button
{
public:
	Button(const char* text, Vector2 buttonPosition);
	~Button();
	void Draw();
	bool isPressed(Vector2 mousePos, bool mousePressed);
private:
	Rectangle buttonSize;
};

/*

In Main :
Button buttonName( text , buttonPosition );

In Main Loop :

Vector2 mousePosition = GetMousePosition();
bool mousePressed = IsMousePressed(MOUSE_BUTTON_LEFT);

if(buttonName.isPressed(mousePosition, mousePressed))
{
	Action
}

*/

