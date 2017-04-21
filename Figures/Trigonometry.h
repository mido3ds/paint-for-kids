#pragma once

#include "../DEFS.h"
#include <cmath>

class Trigonometry {
public:
	// TODO: make this static method
	double Area(Point p1, Point p2, Point p3) const
	{
		return abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2);
	}
};
