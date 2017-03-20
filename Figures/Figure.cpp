#include "Figure.h"

Figure::Figure(const Figure& figure_gfx_info)
{
    draw_clr = figure_gfx_info.draw_clr;
    fill_clr = figure_gfx_info.fill_clr;
    is_filled = figure_gfx_info.is_filled;
    border_width = figure_gfx_info.border_width;
    z_index = figure_gfx_info.z_index;
}

Figure::Figure()
{}

Figure(color draw_clr, color fill_clr, bool is_filled, int border_width,
    int z_index)
{
    this->draw_clr = draw_clr;
    this->fill_clr = fill_clr;
    this->is_filled = is_filled;
    this->border_width = border_width;
    this->z_index = z_index;
}

void Figure::SetSelected(bool s)
{
    selected = s;
}

bool Figure::IsSelected() const
{
    return selected;
}

void Figure::ChngDrawClr(color draw_clr)
{
    draw_clr = draw_clr;
}

void Figure::ChngFillClr(color filling_clr)
{
    is_filled = true;
    fill_clr = filling_clr;
}