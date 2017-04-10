#include "CTrngl.h"

CTrngl::CTrngl()
    : p1(0, 0)
    , p2(0, 0)
    , p3(0, 0)
{
}

CTrngl::CTrngl(Point p1, Point p2, Point p3, GfxInfo trngl_gfx_info)
    : CFigure(trngl_gfx_info)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

void CTrngl::Draw(Output* out_p) const
{
    out_p->DrawTriangle(p1, p2, p3, *this, selected);
}

void CTrngl::Save(ofstream& out_file)
{
    out_file << "CIRCLE" << ' '
             << id << ' '
             << p1 << ' '
             << p2 << ' '
             << p3 << ' '
             << DrawColor << ' '
             << FillColor << ' '
             << '\n';
}

void CTrngl::Load(ifstream& in_file)
{
    in_file >> id
        >> p1
        >> p2
        >> p3
        >> DrawColor
        >> FillColor;
}