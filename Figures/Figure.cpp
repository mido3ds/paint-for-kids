#include "Figure.h"

CFigure::CFigure(const CFigure& figure_gfx_info)
{
    draw_clr = figure_gfx_info.draw_clr;
    fill_clr = figure_gfx_info.fill_clr;
    is_filled = figure_gfx_info.is_filled;
    border_width = figure_gfx_info.border_width;
    z_index = figure_gfx_info.z_index;
}

CFigure::CFigure()
{}

void CFigure::SetSelected(bool s)
{
    selected = s;
}

bool CFigure::IsSelected() const
{
    return selected;
}

void CFigure::Draw(Output * out_p) const
{}

void CFigure::ChngDrawClr(color draw_clr)
{
    draw_clr = draw_clr;
}

void CFigure::ChngFillClr(color filling_clr)
{
    is_filled = true;
    fill_clr = filling_clr;
}

void CFigure::ChngZIndex(int ind)
{
    z_index = abs(ind);
}

void CFigure::ChngBorderWidth(int width)
{
    border_width = abs(width);
}

bool CFigure::IsFilled()
{
    return is_filled;
}

color CFigure::GetDrawClr()
{
    return draw_clr;
}

color CFigure::GetFillClr()
{
    return fill_clr;
}

int CFigure::GetBorderWidth()
{
    return border_width;
}

int CFigure::GetZIndex()
{
    return z_index;
}

void CFigure::Rotate()
	{
	}

void CFigure::Resize()
	{
	}

void CFigure::Move()
	{
	}

void CFigure::Save(ofstream & out_file)
	{
	}

void CFigure::Load(ifstream & in_file)
	{
	}

void CFigure::PrintInfo(Output * out_p)
	{
	}
