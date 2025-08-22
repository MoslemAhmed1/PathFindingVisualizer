#include "Button.h"

Button::Button(const char* text, Vector2 buttonPosition)
{
	// Get text width

	buttonSize.x = buttonPosition.x;
	buttonSize.y = buttonPosition.y;
}

Button::~Button()
{

}

void Button::Draw()
{
	// Use DrawRectangle Function
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
	if (CheckCollisionPointRec(mousePos, buttonSize) && mousePressed)
	{
		return true;
	}
	
	return false;
}
