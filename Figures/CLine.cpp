#include "CLine.h"

CLine::CLine()
    : p1(0, 0)
    , p2(0, 0)
{
}
CLine::CLine(Point p1, Point p2, GfxInfo line_gfx_info)
    : CFigure(line_gfx_info)
{
    this->p1 = p1;
    this->p2 = p2;
}

void CLine::Draw(Output* out_p) const
{
    out_p->DrawLine(p1, p2, *this, selected);
}

void CLine::Save(ofstream& out_file)
{
    out_file << "LINE" << ' '
             << id << ' '

             << p1.x << ' '
             << p1.y << ' '

             << p2.x << ' '
             << p2.y << ' '

             << draw_clr.ucRed << ' '
             << draw_clr.ucGreen << ' '
             << draw_clr.ucBlue << ' '

             << '\n';
}

void CLine::Load(ifstream& in_file)
{
    in_file >> id

        >> p1.x
        >> p1.y

        >> p2.x
        >> p2.y

        >> draw_clr.ucRed
        >> draw_clr.ucGreen
        >> draw_clr.ucBlue;
}