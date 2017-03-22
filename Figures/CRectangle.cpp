#include "CRectangle.h"

CRectangle::CRectangle(Point p1, Point p2, GfxInfo figure_gfx_info)
    :CFigure(figure_gfx_info)
{
    corner1 = p1;
    corner2 = p2;
}

CRectangle::CRectangle()
{}

void CRectangle::Draw(Output* out_p) const
{
    //Call Output::DrawRect to draw a rectangle on the screen
    out_p->DrawRect(corner1, corner2, *this, selected);
}