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
	Point c = CalcCenter();
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

void CLine::Rotated(bool r)
{
	rotate = r;
}

bool CLine::IsRotate()
{
	return rotate;
}

void CLine::Rotate(int deg)
{
    Point c = CalcCenter();
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
        } else {
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
        } else {
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
        } else {
            rotate = true;
            p1 = temp3;
            p2 = temp4;
        }
        break;
    default:
        break;
    }
}

void CLine::Rotated(bool r)
{
    rotate = r;
}

bool CLine::IsRotate()
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

		<< '\n';
}

void CLine::Load(ifstream& in_file)
{
	in_file >> id

		>> p1.x
		>> p1.y

		>> p2.x
		>> p2.y

<<<<<<< HEAD
        >> draw_clr.ucRed
        >> draw_clr.ucGreen
        >> draw_clr.ucBlue;
}

Point CLine::CalcCenter()
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
bool CLine::PointCheck(Point p) const
{
    if (p1.x != p2.x) {
        float m = (float)(p1.y - p2.y) / (p1.x - p2.x);
        return (((float)p.y - p.x * m) == ((float)p1.y - p1.x * m));
    } else
        return (((p.y >= p1.y) && (p.y <= p2.y)) || ((p.y >= p2.y) && (p.y <= p1.y)));
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
    c.z_index = this->z_index;
    CFigure* copy = new CLine(p1, p2, c);
    return copy;
}
=======
		>> draw_clr.ucRed
		>> draw_clr.ucGreen
		>> draw_clr.ucBlue;
}

void CLine::Resize(int resize_factor)
{
	Point c = CalcCenter();
	p1.x = (int(resize_factor * (p1.x - c.x))) + c.x;
	p1.y = (int(resize_factor * (p1.y - c.y))) + c.y;
	p2.x = (int(resize_factor * (p2.x - c.x))) + c.x;
	p2.y = (int(resize_factor * (p2.y - c.y))) + c.y;
}

Point CLine::CalcCenter()
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
>>>>>>> abdo
