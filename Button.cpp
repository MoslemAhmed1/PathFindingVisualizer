#include "Button.h"

Button::Button(Rectangle bounds, ButtonType type) : buttonBounds(bounds), buttonType(type)
{}

Button::~Button()
{}

bool Button::isPressed(Vector2 mousePos) const
{
	return CheckCollisionPointRec(mousePos, buttonBounds);
}
