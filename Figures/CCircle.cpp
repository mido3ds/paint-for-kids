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

bool CCircle::IsRotate()
{
    return rotate;
}

Point CCircle::CalcCenter()
{
    return p1;
}

bool CCircle::OutOfRange(Point p1)
{
    return (p1.x - GetRadius() < UI.DrawAreaX || p1.x + GetRadius() > UI.DrawAreaX + UI.DrawAreaWidth || p1.y - GetRadius() < UI.DrawAreaY || p1.y + GetRadius() > UI.DrawAreaY + UI.DrawAreaHeight);
}

Point CCircle::GetSecondPointFromRadius(double rad)
{
    return Point(p1.x, p1.y + rad);
}

void CCircle::Draw(Output* out_p) const
{
    out_p->DrawCircle(p1, p2, *this, selected);
}

void CCircle::Rotate(int deg)
{
}

void CCircle::Rotated(bool r)
{
    rotate = r;
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

bool CCircle::PointCheck(Point p) const
{
    float RadiusSquare = pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
    float NewDistance = pow(p.x - p1.x, 2) + pow(p.y - p1.y, 2);
    return (NewDistance <= RadiusSquare);
}

bool CCircle::Move(int x, int y)
{
    Point tp1, tp2;
    tp1.x = p1.x + x;
    tp1.y = p1.y + y;
    tp2.x = p2.x + x;
    tp2.y = p2.y + y;
    if (!OutOfRange(p1)) {
        p1 = tp1;
        p2 = tp2;
        return true;
    }
    return false;
}

CFigure* CCircle::Copy()
{
    GfxInfo c;
    c.border_width = this->border_width;
    c.draw_clr = this->draw_clr;
    c.fill_clr = this->fill_clr;
    c.is_filled = this->is_filled;
    c.z_index = this->z_index;
    CFigure* copy = new CCircle(p1, p2, c);
    return copy;
}