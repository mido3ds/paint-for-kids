#include "Rectangle.h"

Rectangle::Rectangle(Point p1, Point p2, GfxInfo figure_gfx_info)
    : Figure(figure_gfx_info)
{
    corner1 = p1;
    corner2 = p2;
}

void Rectangle::Draw(Output* out_p) const
{
    //Call Output::DrawRect to draw a rectangle on the screen
    out_p->DrawRect(corner1, corner2, fig_gfx_info, selected);
}