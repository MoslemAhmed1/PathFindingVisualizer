#include "Button.h"

Button::Button(string text, Vector2 position, ButtonType type)
{
	buttonText = text;
	buttonBounds = { position.x, position.y, (float) UI.ButtonWidth, (float) UI.ButtonHeight };
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
