#pragma once

#include "DEFS.h"

class Button
{
public:

	ButtonType buttonType;

	Rectangle buttonBounds;
	
	Button(Rectangle bounds, ButtonType type);
	
	bool isPressed(Vector2 mousePos) const;

	~Button();
};

