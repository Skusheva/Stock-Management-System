#pragma once
#include <string>

struct Location {
	size_t x;
	size_t y;

	Location() : x(0), y(0) {}
	Location(size_t x_, size_t y_) : x(x_), y(y_) {}
};

size_t getValidCoordinate();
Location inputLocation();
