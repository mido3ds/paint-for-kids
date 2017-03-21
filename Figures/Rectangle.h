#ifndef CRECT_H
#define CRECT_H

#include "Figure.h"

class CRectangle : public CFigure {
public:
    CRectangle();
    CRectangle(Point, Point, CFigure figure_gfx_info);
    
    virtual void Draw(Output* out_p) const;

private:
    Point corner1;
    Point corner2;
};

#endif