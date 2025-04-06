#include "Gauge.h"

Gauge::Gauge(float maxGauge, Rectangle rect, Color color) 
			: _currentGauge(maxGauge), _maxGauge(maxGauge), _rect(rect), _color(color) {}

void Gauge::draw() {
	float ratio = _currentGauge / _maxGauge;

    DrawRectangle(_rect.x, _rect.y, _rect.width, _rect.height, GRAY);
    DrawRectangle(_rect.x, _rect.y, _rect.width * ratio, _rect.height, _color);
}

void Gauge::update(float value) {
	_currentGauge = value;
}