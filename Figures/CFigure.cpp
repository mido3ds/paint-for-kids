#include "CFigure.h"

CFigure::CFigure(const GfxInfo& figure_gfx_info)
{
	draw_clr = figure_gfx_info.draw_clr;
	fill_clr = figure_gfx_info.fill_clr;
	is_filled = figure_gfx_info.is_filled;
	border_width = figure_gfx_info.border_width;
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

bool CFigure::OutOfRightRange(const Point& p) const
{
	return !((p.x > UI.width / 2) && (p.x < UI.width)) && ((p.y > 50) && (p.y < UI.StatusBarY));
}

void CFigure::SetDrawColor(color draw_clr)
{
	this->draw_clr = draw_clr;
}

void CFigure::SetFillColor(color filling_clr)
{
	is_filled = (filling_clr != WHITE);
	fill_clr = filling_clr;
}

void CFigure::SetBorderWidth(int BW)
{
	if (BW > 0)
		border_width = BW;
	else 
		cerr << "border width of figure cant be <= 0, given border width is " << BW << "\n";
}

void CFigure::SetId(unsigned int id)
{
	this->id = id;
}

unsigned int CFigure::GetId() const
{
	return id;
}

color CFigure::GetDrawColor() const
{
	return draw_clr;
}

color CFigure::GetFillColor() const
{
	return fill_clr;
}

int CFigure::GetBorderWidth() const
{
	return border_width;
}

bool CFigure::IsFilled() const
{
	return is_filled;
}