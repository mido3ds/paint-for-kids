#include "CLine.h"

CLine::CLine()
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

void CLine::Rotate(int deg)
{
	Point c = CalculateCenter();
	Point temp1 = p1;
	Point temp2 = p2;
	Point temp3;
	Point temp4;
	temp1.x -= c.x;
	temp2.x -= c.x;
	temp1.y -= c.y;
	temp2.y -= c.y;
	temp3.x = temp1.y * -1;
	temp3.y = temp1.x;
	temp4.x = temp2.y * -1;
	temp4.y = temp2.x;
	temp3.x += c.x;
	temp4.x += c.x;
	temp3.y += c.y;
	temp4.y += c.y;
	if (IsOutOfRange(temp3, temp4))
	{
		is_rotated = false;
	}
	else {
		is_rotated = true;
		p1 = temp3;
		p2 = temp4;
	}
}

void CLine::SetRotated(bool r)
{
	is_rotated = r;
}

bool CLine::IsRotated()
{
	return is_rotated;
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

		<< border_width

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
        >> draw_clr.ucBlue
		
		>> border_width;
}

bool CLine::IsPointInside(const Point& p) const
{
	double d1 = sqrt(pow(p.x - p1.x, 2) + pow(p.y - p1.y, 2));
	double d2 = sqrt(pow(p.x - p2.x, 2) + pow(p.y - p2.y, 2));
	double d = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	double c = d1 + d2;
	double scale = 0.1;
	c = (int)(c / scale)*scale;
	d = (int)(d / scale)*scale;
	return (c == d);
}

bool CLine::Move(int x, int y)
{
    Point tp1, tp2;
    tp1.x = p1.x + x;
    tp1.y = p1.y + y;
    tp2.x = p2.x + x;
    tp2.y = p2.y + y;
    if (!IsOutOfRange(tp1, tp2)) {
        p1 = tp1;
        p2 = tp2;
        return true;
    }
    return false;
}

CFigure* CLine::Copy()
{
    GfxInfo c;
    c.border_width = this->border_width;
    c.draw_clr = this->draw_clr;
    c.fill_clr = this->fill_clr;
    c.is_filled = this->is_filled;

    CFigure* copy = new CLine(p1, p2, c);

	copy->SetSelected(this->IsSelected());
	copy->SetId(this->GetId());
	
    return copy;
}

string CLine::GetType()
{
	return type;
}

double CLine::GetArea()
{
	double length = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	return length;
}

bool CLine::CheckResize(double resize_factor)
{
	Point new_p1;
	Point new_p2;
	Point c = CalculateCenter();
	new_p1.x = (int(resize_factor * (p1.x - c.x))) + c.x;
	new_p1.y = (int(resize_factor * (p1.y - c.y))) + c.y;
	new_p2.x = (int(resize_factor * (p2.x - c.x))) + c.x;
	new_p2.y = (int(resize_factor * (p2.y - c.y))) + c.y;

	if (IsOutOfRange(new_p1, new_p2))
		return false;

	return true;
}

void CLine::Resize(double resize_factor)
{
	Point c = CalculateCenter();
	p1.x = (int(resize_factor * (p1.x - c.x))) + c.x;
	p1.y = (int(resize_factor * (p1.y - c.y))) + c.y;
	p2.x = (int(resize_factor * (p2.x - c.x))) + c.x;
	p2.y = (int(resize_factor * (p2.y - c.y))) + c.y;
}

void CLine::Drag(const Point& p, Corners corner)
{
	if (corner == LINE_1)
		p1 = p;
	else if (corner == LINE_2)
		p2 = p;
}

void CLine::DragPoints(Output* out_p, const GfxInfo& info) const
{
	out_p->DrawCircle(p1, 4, info, false);
	out_p->DrawCircle(p2, 4, info, false);
}

Point CLine::CalculateCenter()
{
	Point c;
	c.x = (p1.x + p2.x) / 2;
	c.y = (p1.y + p2.y) / 2;
	return c;
}

bool CLine::IsOutOfRange(Point p1, Point p2)
{
	return (p1.y < UI.DrawAreaY || p1.y > UI.DrawAreaY + UI.DrawAreaHeight || p1.x < UI.DrawAreaX || p1.x > UI.DrawAreaX + UI.DrawAreaWidth || p2.y < UI.DrawAreaY || p2.y > UI.DrawAreaY + UI.DrawAreaHeight || p2.x < UI.DrawAreaX || p2.x > UI.DrawAreaX + UI.DrawAreaWidth);
}

void CLine::PrintInfo(Output* out_p)
{
	out_p->PrintMessage("Line... ID:" + to_string(this->GetId()) + " Start:(" + to_string(p1.x) + "," + to_string(p1.y) + ") End:(" + to_string(p2.x) + "," + to_string(p2.y) + ")", WHITE, true);
}

void CLine::SetPoints(Point p1, Point p2)
{
	this->p1 = p1;
	this->p2 = p2;
}

void CLine::MoveToLeftSide()
{
	Point center = CalculateCenter();

	// get difference between center and points
	int def1 = p1.x - center.x;
	int def2 = p2.x - center.x;

	center.x /= 2;

	// remake the points from the previous centere
	p1.x = center.x + def1;
	p2.x = center.x + def2;
}

void CLine::RandomizePosition()
{
	Point center = CalculateCenter();

	// get difference between center and points
	Point def1(p1.x - center.x, p1.y - center.y);
	Point def2(p2.x - center.x, p2.y - center.y);
	int i = 0;
	do
	{
		center.x = rand() % (((UI.width - 5) - ((UI.width / 2) + 5)) + 1) + ((UI.width / 2) + 5);
		center.y = rand() % (((UI.StatusBarY - 5) - 55) + 1) + 55;

		p1 = center + def1;
		p2 = center + def2;
		i++;
	} while (OutOfRightRange(p1) || OutOfRightRange(p2));
}

Corners CLine::GetCornerPoint(const Point& p) const
{
	if (((p.x - p1.x) >= -4 && (p.x - p1.x) <= 4) && ((p.y - p1.y) >= -4 && (p.y - p1.y) <= 4))
		return LINE_1;
	else if (((p.x - p2.x) >= -4 && (p.x - p2.x) <= 4) && ((p.y - p2.y) >= -4 && (p.y - p2.y) <= 4))
		return LINE_2;
	else
		return INVALID;
}

void CLine::SetAll(CFigure* fig)
{
	CLine* line;
	if ((line = dynamic_cast<CLine*>(fig)) == nullptr)
		return;

	this->border_width = line->border_width;
	this->draw_clr = line->draw_clr;
	this->fill_clr = line ->fill_clr;
	this->is_filled = line->is_filled;

	SetSelected(fig->IsSelected());
	SetId(fig->GetId());

	this->p1 = line->p1;
	this->p2 = line->p2;

}