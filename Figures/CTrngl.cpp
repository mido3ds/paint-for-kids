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

void CTrngl::Rotate(int deg)
{
	Point c = CalcCenter();
	Point temp1 = p1;
	Point temp2 = p2;
	Point temp3 = p3;
	Point temp5 = p3;
	Point temp4;
	Point temp6;
	switch (deg) {
	case 90:
		temp1.x -= c.x;
		temp2.x -= c.x;
		temp5.x -= c.x;
		temp1.y -= c.y;
		temp2.y -= c.y;
		temp5.y -= c.y;
		temp3.x = temp1.y * -1;
		temp3.y = temp1.x;
		temp4.x = temp2.y * -1;
		temp4.y = temp2.x;
		temp6.x = temp5.y * -1;
		temp6.y = temp5.x;
		temp3.x += c.x;
		temp4.x += c.x;
		temp6.x += c.x;
		temp3.y += c.y;
		temp4.y += c.y;
		temp6.y += c.y;
		if (OutOfRange(temp3, temp4, temp6)) // To Be Edited With The New Layout
		{
			rotate = false;
		}
		else {
			rotate = true;
			p1 = temp3;
			p2 = temp4;
			p3 = temp6;
		}
		break;
	case 180:
		temp1.x = (2 * c.x) - temp1.x;
		temp2.x = (2 * c.x) - temp2.x;
		temp3.x = (2 * c.x) - temp3.x;
		temp1.y = (2 * c.y) - temp1.y;
		temp2.y = (2 * c.y) - temp2.y;
		temp3.y = (2 * c.y) - temp3.y;
		if (OutOfRange(temp1, temp2, temp3)) {
			rotate = false;
		}
		else {
			rotate = true;
			p1 = temp1;
			p2 = temp2;
			p3 = temp3;
		}
		break;
	case 270:
		temp1.x -= c.x;
		temp2.x -= c.x;
		temp5.x -= c.x;
		temp1.y -= c.y;
		temp2.y -= c.y;
		temp5.y -= c.y;
		temp3.x = temp1.y;
		temp3.y = temp1.x * -1;
		temp4.x = temp2.y;
		temp4.y = temp2.x * -1;
		temp6.x = temp5.y;
		temp6.y = temp5.x * -1;
		temp3.x += c.x;
		temp4.x += c.x;
		temp6.x += c.x;
		temp3.y += c.y;
		temp4.y += c.y;
		temp6.y += c.y;
		if (OutOfRange(temp3, temp4, temp6)) // To Be Edited With The New Layout
		{
			rotate = false;
		}
		else {
			rotate = true;
			p1 = temp3;
			p2 = temp4;
			p3 = temp6;
		}
		break;
	default:
		break;
	}
}

void CTrngl::Rotated(bool r)
{
	rotate = r;
}

bool CTrngl::IsRotate()
{
	return rotate;
}

void CTrngl::Resize(int resize_factor)
{
	Point c = CalcCenter();
	p1.x = (int(resize_factor * (p1.x - c.x))) + c.x;
	p1.y = (int(resize_factor * (p1.y - c.y))) + c.y;
	p2.x = (int(resize_factor * (p2.x - c.x))) + c.x;
	p2.y = (int(resize_factor * (p2.y - c.y))) + c.y;
	p3.x = (int(resize_factor * (p3.x - c.x))) + c.x;
	p3.y = (int(resize_factor * (p3.y - c.y))) + c.y;
}

void CTrngl::Rotate(int deg)
{
    Point c = CalcCenter();
    Point temp1 = p1;
    Point temp2 = p2;
    Point temp3 = p3;
    Point temp5 = p3;
    Point temp4;
    Point temp6;
    switch (deg) {
    case 90:
        temp1.x -= c.x;
        temp2.x -= c.x;
        temp5.x -= c.x;
        temp1.y -= c.y;
        temp2.y -= c.y;
        temp5.y -= c.y;
        temp3.x = temp1.y * -1;
        temp3.y = temp1.x;
        temp4.x = temp2.y * -1;
        temp4.y = temp2.x;
        temp6.x = temp5.y * -1;
        temp6.y = temp5.x;
        temp3.x += c.x;
        temp4.x += c.x;
        temp6.x += c.x;
        temp3.y += c.y;
        temp4.y += c.y;
        temp6.y += c.y;
        if (OutOfRange(temp3, temp4, temp6)) // To Be Edited With The New Layout
        {
            rotate = false;
        } else {
            rotate = true;
            p1 = temp3;
            p2 = temp4;
            p3 = temp6;
        }
        break;
    case 180:
        temp1.x = (2 * c.x) - temp1.x;
        temp2.x = (2 * c.x) - temp2.x;
        temp3.x = (2 * c.x) - temp3.x;
        temp1.y = (2 * c.y) - temp1.y;
        temp2.y = (2 * c.y) - temp2.y;
        temp3.y = (2 * c.y) - temp3.y;
        if (OutOfRange(temp1, temp2, temp3)) {
            rotate = false;
        } else {
            rotate = true;
            p1 = temp1;
            p2 = temp2;
            p3 = temp3;
        }
        break;
    case 270:
        temp1.x -= c.x;
        temp2.x -= c.x;
        temp5.x -= c.x;
        temp1.y -= c.y;
        temp2.y -= c.y;
        temp5.y -= c.y;
        temp3.x = temp1.y;
        temp3.y = temp1.x * -1;
        temp4.x = temp2.y;
        temp4.y = temp2.x * -1;
        temp6.x = temp5.y;
        temp6.y = temp5.x * -1;
        temp3.x += c.x;
        temp4.x += c.x;
        temp6.x += c.x;
        temp3.y += c.y;
        temp4.y += c.y;
        temp6.y += c.y;
        if (OutOfRange(temp3, temp4, temp6)) // To Be Edited With The New Layout
        {
            rotate = false;
        } else {
            rotate = true;
            p1 = temp3;
            p2 = temp4;
            p3 = temp6;
        }
        break;
    default:
        break;
    }
}

void CTrngl::Rotated(bool r)
{
    rotate = r;
}

bool CTrngl::IsRotate()
{
    return rotate;
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

<<<<<<< HEAD
        >> fill_clr.ucRed
        >> fill_clr.ucGreen
        >> fill_clr.ucBlue;
=======
		>> fill_clr.ucRed
		>> fill_clr.ucGreen
		>> fill_clr.ucBlue;
>>>>>>> abdo
}

Point CTrngl::CalcCenter()
{
<<<<<<< HEAD
    Point c;
    double x12 = p1.x - p2.x,
           x13 = p1.x - p3.x,
           y12 = p1.y - p2.y,
           y13 = p1.y - p3.y;
    double x1 = p1.x * p1.x,
           x2 = p2.x * p2.x,
           x3 = p3.x * p3.x,
           y1 = p1.y * p1.y,
           y2 = p2.y * p2.y,
           y3 = p3.y * p3.y;
    c.y = (-1 * ((x1 - x3 + y1 - y3) * (x12 / x13)) + x1 - x2 + y1 - y2) / ((2 * y12) - ((x12 / x13) * 2 * y13));
    c.x = (x1 - x2 + y1 - y2 - (2 * y12 * c.y)) / (2 * x12);
    return c;
=======
	Point c;
	double x12 = p1.x - p2.x,
		x13 = p1.x - p3.x,
		y12 = p1.y - p2.y,
		y13 = p1.y - p3.y;
	double x1 = p1.x * p1.x,
		x2 = p2.x * p2.x,
		x3 = p3.x * p3.x,
		y1 = p1.y * p1.y,
		y2 = p2.y * p2.y,
		y3 = p3.y * p3.y;
	c.y = (-1 * ((x1 - x3 + y1 - y3) * (x12 / x13)) + x1 - x2 + y1 - y2) / ((2 * y12) - ((x12 / x13) * 2 * y13));
	c.x = (x1 - x2 + y1 - y2 - (2 * y12 * c.y)) / (2 * x12);
	return c;
>>>>>>> abdo
}

bool CTrngl::OutOfRange(Point p1, Point p2, Point p3)
{
<<<<<<< HEAD
    return (p1.y < UI.ToolBarHeight || p1.y > UI.height - UI.StatusBarHeight || p1.x < 0 || p1.x > UI.width || p2.y < UI.ToolBarHeight || p2.y > UI.height - UI.StatusBarHeight || p2.x < 0 || p2.x > UI.width || p3.y < UI.ToolBarHeight || p3.y > UI.height - UI.StatusBarHeight || p3.x < 0 || p3.x > UI.width);
}
bool CTrngl::PointCheck(Point p) const
{
    float A1 = Trigonometry::Area(p, p1, p2);
    float A2 = Trigonometry::Area(p, p2, p3);
    float A3 = Trigonometry::Area(p, p1, p3);
    float A = Trigonometry::Area(p1, p2, p3);
    return (A == A1 + A2 + A3);
}

bool CTrngl::Move(int x, int y)
{
    Point tp1, tp2, tp3;
    tp1.x = p1.x + x;
    tp1.y = p1.y + y;
    tp2.x = p2.x + x;
    tp2.y = p2.y + y;
    tp3.x = p3.x + x;
    tp3.y = p3.y + y;
    if (!OutOfRange(tp1, tp2, tp3)) {
        p1 = tp1;
        p2 = tp2;
        p3 = tp3;
        return true;
    }
    return false;
}

CFigure* CTrngl::Copy()
{
    GfxInfo c;
    c.border_width = this->border_width;
    c.draw_clr = this->draw_clr;
    c.fill_clr = this->fill_clr;
    c.is_filled = this->is_filled;
    c.z_index = this->z_index;
    CFigure* copy = new CTrngl(p1, p2, p3, c);
    return copy;
}
=======
	return (p1.y < UI.ToolBarHeight || p1.y > UI.height - UI.StatusBarHeight || p1.x < 0 || p1.x > UI.width || p2.y < UI.ToolBarHeight || p2.y > UI.height - UI.StatusBarHeight || p2.x < 0 || p2.x > UI.width || p3.y < UI.ToolBarHeight || p3.y > UI.height - UI.StatusBarHeight || p3.x < 0 || p3.x > UI.width);
}
>>>>>>> abdo
