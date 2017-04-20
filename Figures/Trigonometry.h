#pragma once

#include "../DEFS.h"
#include <cmath>

class Trigonometry {
public:
    Trigonometry();
    float Area(Point p1, Point p2, Point p3) const;
    ~Trigonometry();
};
