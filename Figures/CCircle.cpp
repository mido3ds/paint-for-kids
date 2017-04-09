#include "CCircle.h"

CCircle::CCircle()
    :p1(0, 0), p2(0, 0)
{}
CCircle::CCircle(Point p1, Point p2, GfxInfo circ_gfx_info)
    : CFigure(circ_gfx_info)
{
    this->p1 = p1;
    this->p2 = p2;
}

void CCircle::Draw(Output* out_p) const
{
    out_p->DrawCircle(p1, p2, *this, selected);
}