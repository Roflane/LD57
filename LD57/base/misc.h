#pragma once
#include "raylib.h"
#include "../base/typedefs.h"
#include <cmath>

template <typename T>
T max(T value1, T value2) {
	return (value1 > value2) ? value1 : value2;
}
template <typename T>
T min(T value1, T value2) {
	return (value1 < value2) ? value1 : value2;
}

template <typename T>
T& clamp(T trackValue, T minValue, T maxValue) {
	if (trackValue < minValue) { trackValue = minValue; }
	if (trackValue > maxValue) { trackValue = maxValue; }
	return trackValue;
}

static float NormalizeVector2(float x, float y) {
	return std::sqrt(x * x + y * y);
}

static Color GetMixColor(Color color1, Color color2) {
	return Color(
		(max(0, color1.r + color2.r)),
		(max(0, color1.g + color2.g)),
		(min<unsigned char>(max(color1.b, color2.b), color1.b + color2.b)),
		255
	);
}

static bool isCursorOnImage(int mx, int my, int imgX, int imgY, int imgWidth, int imgHeight) {
	return (mx >= imgX && mx < imgX + imgWidth) &&
		(my >= imgY - 18 && my < imgY - 18 + imgHeight);
}