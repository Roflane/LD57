#pragma once
#include <raylib.h>
#include "../../../base/typedefs.h"
#include "../../../base/misc.h"
#include "../../settings/GlobalSettings.h"

class Tooltip {
private:
	// Fields
	Rectangle _rect;
	Color _color;
	bool _showing;
public:
	Tooltip(Rectangle rect, Color color);

	// Properties
	Vector2 getPos() const { return Vector2(_rect.x, _rect.y); }
	void setPos(Vector2 pos) { _rect.x = pos.x; _rect.y = pos.y; }

	// Methods 
	void spawn(const char* text, ushort fontSize, Color color);
	void update(Vector2 pos, ushort mx, ushort my);
};