#ifndef CRECT_H
#define CRECT_H

#include "Figure.h"

class Rectangle : public Figure {
public:
    Rectangel();
    Rectangle(Point, Point, GfxInfo figure_gfx_info);
    
    virtual void Draw(Output* out_p) const;

private:
    Point corner1;
    Point corner2;
};

#endif