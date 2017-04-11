#include "CCircle.h"

CCircle::CCircle()
    : p1(0, 0)
    , p2(0, 0)
{
}
CCircle::CCircle(Point p1, Point p2, GfxInfo circ_gfx_info)
    : CFigure(circ_gfx_info)
{
    this->p1 = p1;
    this->p2 = p2;
}

double CCircle::GetRadius()
{
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

Point CCircle::GetSecondPointFromRadius(double rad)
{
    return Point(p1.x, p1.y + rad);
}

void CCircle::Draw(Output* out_p) const
{
    out_p->DrawCircle(p1, p2, *this, selected);
}

void CCircle::Save(ofstream& out_file)
{
    out_file << "CIRCLE" << ' '
             << id << ' '

             << p1.x << ' '
             << p1.y << ' '

             << GetRadius() << ' '

             << draw_clr.ucRed << ' '
             << draw_clr.ucGreen << ' '
             << draw_clr.ucBlue << ' '

             << fill_clr.ucRed << ' '
             << fill_clr.ucGreen << ' '
             << fill_clr.ucBlue << ' '

             << '\n';
}

void CCircle::Load(ifstream& in_file)
{
    double rad;
    in_file >> id

        >> p1.x
        >> p1.y

        >> rad

        >> draw_clr.ucRed
        >> draw_clr.ucGreen
        >> draw_clr.ucBlue

        >> fill_clr.ucRed
        >> fill_clr.ucGreen
        >> fill_clr.ucBlue;

    p2 = GetSecondPointFromRadius(rad);
}