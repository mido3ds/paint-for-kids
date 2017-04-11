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
    out_file << "TRIANGLE" << ' '
             << id << ' '

             << p1.x << ' '
             << p1.y << ' '

             << p2.x << ' '
             << p2.y << ' '

             << p3.x << ' '
             << p3.y << ' '

             << draw_clr.ucRed << ' '
             << draw_clr.ucGreen << ' '
             << draw_clr.ucBlue << ' '

             << fill_clr.ucRed << ' '
             << fill_clr.ucGreen << ' '
             << fill_clr.ucBlue << ' '

             << '\n';
}

void CTrngl::Load(ifstream& in_file)
{
    in_file >> id

        >> p1.x
        >> p1.y

        >> p2.x
        >> p2.y

        >> p3.x
        >> p3.y

        >> draw_clr.ucRed
        >> draw_clr.ucGreen
        >> draw_clr.ucBlue

        >> fill_clr.ucRed
        >> fill_clr.ucGreen
        >> fill_clr.ucBlue;
}