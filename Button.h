#pragma once
#include "raylib.h"
#include "DEFS.h"

class Button
{
public:

	ButtonType buttonType;

	Rectangle buttonBounds;

	string buttonText;
	
	Button(string text, Rectangle bounds, ButtonType type);
	
	bool isPressed(Vector2 mousePos) const;

	~Button();
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

