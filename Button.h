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

