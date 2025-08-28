#include "Button.h"

Button::Button(string text, Rectangle bounds, ButtonType type)
{
	buttonText = text;
	buttonBounds = bounds;
	buttonType = type;
}

Button::~Button()
{

}

bool Button::isPressed(Vector2 mousePos) const
{
	if (CheckCollisionPointRec(mousePos, buttonBounds))
	{
		return true;
	}
	
	return false;
}
