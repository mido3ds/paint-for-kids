#include "CFigure.h"

CFigure::CFigure(const GfxInfo& figure_gfx_info)
{
    draw_clr = figure_gfx_info.draw_clr;
    fill_clr = figure_gfx_info.fill_clr;
    is_filled = figure_gfx_info.is_filled;
    border_width = figure_gfx_info.border_width;
    z_index = figure_gfx_info.z_index;
}

CFigure::CFigure()
{
}

void CFigure::SetSelected(bool s)
{
    selected = s;
}

bool CFigure::IsSelected() const
{
    return selected;
}

void CFigure::ChngDrawClr(color draw_clr)
{
    this->draw_clr = draw_clr;
}

void CFigure::ChngFillClr(color filling_clr)
{
    is_filled = true;
    this->fill_clr = filling_clr;
}

void CFigure::SetId(unsigned int id)
{
    this->id = id;
}

unsigned int CFigure::GetId()
{
    return id;
}