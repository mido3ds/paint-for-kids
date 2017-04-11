#include "CLine.h"

CLine::CLine()
    :p1(0, 0), p2(0, 0)
{}
CLine::CLine(Point p1, Point p2, GfxInfo line_gfx_info)
    :CFigure(line_gfx_info)
{
    this->p1 = p1;
    this->p2 = p2;
}

void CLine::Draw(Output* out_p) const
{
    out_p->DrawLine(p1, p2, *this, selected);
}