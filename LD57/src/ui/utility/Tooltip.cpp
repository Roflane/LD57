#include "Tooltip.h"

Tooltip::Tooltip(Rectangle rect, Color color) : 
	_rect(rect), _color(color), _showing(true) {}

void Tooltip::spawn(const char* text, ushort fontSize, Color color) {
	ushort textOffset = 10;
	ushort widthFinal = MeasureText(text, fontSize);

	float textX = _rect.x + (_rect.width - (widthFinal / 2)) / 2;
	float textY = _rect.y + (_rect.height - fontSize) / 2; 

	if (_showing) {
		DrawRectangle(_rect.x, _rect.y, widthFinal + (textOffset * 2), _rect.height, _color);
		DrawText(text, _rect.x + textOffset, _rect.y + textOffset, fontSize, color);
		DrawText("Click here to close", textX, textY, fontSize, color);
	}
}

void Tooltip::update(Vector2 pos, ushort mx, ushort my) {
	_rect.x = pos.x;
	_rect.y = pos.y;

	if (isCursorOnImage(mx, my, _rect.x, _rect.y, _rect.width, _rect.height) &&
		IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { _showing = false; }
}