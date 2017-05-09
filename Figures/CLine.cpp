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

void CLine::Rotate(int deg)
{
	Point c = CalculateCenter();
	Point temp1 = p1;
	Point temp2 = p2;
	Point temp3;
	Point temp4;
	switch (deg) {
	case 90:
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
		if (OutOfRange(temp3, temp4)) // To Be Edited With The New Layout
		{
			rotate = false;
		}
		else {
			rotate = true;
			p1 = temp3;
			p2 = temp4;
		}
		break;
	case 180:
		temp1.x = (2 * c.x) - temp1.x;
		temp2.x = (2 * c.x) - temp2.x;
		temp1.y = (2 * c.y) - temp1.y;
		temp2.y = (2 * c.y) - temp2.y;
		if (OutOfRange(temp1, temp2)) {
			rotate = false;
		}
		else {
			rotate = true;
			p1 = temp1;
			p2 = temp2;
		}
		break;
	case 270:
		temp1.x -= c.x;
		temp2.x -= c.x;
		temp1.y -= c.y;
		temp2.y -= c.y;
		temp3.x = temp1.y;
		temp3.y = temp1.x * -1;
		temp4.x = temp2.y;
		temp4.y = temp2.x * -1;
		temp3.x += c.x;
		temp4.x += c.x;
		temp3.y += c.y;
		temp4.y += c.y;
		if (OutOfRange(temp3, temp4)) // To Be Edited With The New Layout
		{
			rotate = false;
		}
		else {
			rotate = true;
			p1 = temp3;
			p2 = temp4;
		}
		break;
	default:
		break;
	}
}

void CLine::SetRotated(bool r)
{
	rotate = r;
}

bool CLine::IsRotated()
{
	return rotate;
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

bool CLine::PointCheck(Point p) const
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
    if (!OutOfRange(tp1, tp2)) {
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

void CLine::Resize(double resize_factor)
{
	Point c = CalculateCenter();
	p1.x = (int(resize_factor * (p1.x - c.x))) + c.x;
	p1.y = (int(resize_factor * (p1.y - c.y))) + c.y;
	p2.x = (int(resize_factor * (p2.x - c.x))) + c.x;
	p2.y = (int(resize_factor * (p2.y - c.y))) + c.y;
}

Point CLine::CalculateCenter()
{
	Point c;
	c.x = (p1.x + p2.x) / 2;
	c.y = (p1.y + p2.y) / 2;
	return c;
}

bool CLine::OutOfRange(Point p1, Point p2)
{
	return (p1.y < UI.ToolBarHeight || p1.y > UI.height - UI.StatusBarHeight || p1.x < 0 || p1.x > UI.width || p2.y < UI.ToolBarHeight || p2.y > UI.height - UI.StatusBarHeight || p2.x < 0 || p2.x > UI.width);
}

void CLine::PrintInfo(Output* out_p)
{
	out_p->PrintMessage("Line... ID:" + to_string(this->GetId()) + " Start:(" + to_string(p1.x) + "," + to_string(p1.y) + ") End:(" + to_string(p2.x) + "," + to_string(p2.y) + ")");
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

void CLine::MoveToRightSide()
{
	Point center = CalculateCenter();

	// get difference between center and points
	int def1 = p1.x - center.x;
	int def2 = p2.x - center.x;

	center.x = center.x / 2 + UI.width / 2;

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
		center.x = rand() % ((UI.width - (UI.width / 2)) + 1) + (UI.width / 2);
		center.y = rand() % ((UI.StatusBarY - 50) + 1) + 50;
		p1 = center + def1;
		p2 = center + def2;
		i++;
	} while (OutOfRightRange(p1) || OutOfRightRange(p2));
}