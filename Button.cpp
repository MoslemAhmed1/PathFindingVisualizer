#include "Button.h"

Button::Button(string text, Vector2 position, ButtonType type)
{
	buttonText = text.c_str();
	buttonBounds = { position.x, position.y, (float) UI.ButtonWidth, (float) UI.ButtonHeight };
	buttonType = type;
}

Button::~Button()
{

}

bool Button::isPressed(Vector2 mousePos, bool mousePressed) const
{
	if (CheckCollisionPointRec(mousePos, buttonBounds) && mousePressed)
	{
		return true;
	}
	
	return false;
}
