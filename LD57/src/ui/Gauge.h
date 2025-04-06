#pragma once
#include <raylib.h>
#include "../../base/typedefs.h"

class Gauge {
private:
	// Fields
	float _currentGauge;
	float _maxGauge;
	Rectangle _rect;
	Color _color;
public:
	Gauge(float _maxGauge, Rectangle rect, Color color);

	// Properties
	void setPos(int x, int y) {
		_rect.x = x;
		_rect.y = y;
	}

	// Methods 
	void draw();
	void update(float value);
};