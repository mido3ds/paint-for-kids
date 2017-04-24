#include "CRectangle.h"

CRectangle::CRectangle(Point p1, Point p2, GfxInfo figure_gfx_info)
	: CFigure(figure_gfx_info)
{
	this->p1 = p1;
	this->p2 = p2;
}

CRectangle::CRectangle()
{
}

void CRectangle::Draw(Output* out_p) const
{
	//Call Output::DrawRect to draw a rectangle on the screen
	out_p->DrawRect(p1, p2, *this, selected);
}
void CRectangle::Rotate(int deg)
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
void CRectangle::Rotated(bool r)
{
	rotate = r;
}
bool CRectangle::IsRotate()
{
	return rotate;
}
void CRectangle::Save(ofstream& out_file)
{
	out_file << "RECTANGLE" << ' '
		<< id << ' '

		<< p1.x << ' '
		<< p1.y << ' '

		<< p2.x << ' '
		<< p2.y << ' '

		<< draw_clr.ucRed << ' '
		<< draw_clr.ucGreen << ' '
		<< draw_clr.ucBlue << ' '

		<< fill_clr.ucRed << ' '
		<< fill_clr.ucGreen << ' '
		<< fill_clr.ucBlue << ' '

		<< '\n';
}

void CRectangle::Load(ifstream& in_file)
{
	in_file >> id

		>> p1.x
		>> p1.y

		>> p2.x
		>> p2.y

		>> draw_clr.ucRed
		>> draw_clr.ucGreen
		>> draw_clr.ucBlue

		>> fill_clr.ucRed
		>> fill_clr.ucGreen
		>> fill_clr.ucBlue;
}

void CRectangle::Resize(int resize_factor)
{
	Point c = CalcCenter();
	p1.x = (int(resize_factor * (p1.x - c.x))) + c.x;
	p1.y = (int(resize_factor * (p1.y - c.y))) + c.y;
	p2.x = (int(resize_factor * (p2.x - c.x))) + c.x;
	p2.y = (int(resize_factor * (p2.y - c.y))) + c.y;
}

Point CRectangle::CalcCenter()
{
	Point c;
	c.x = (p1.x + p2.x) / 2;
	c.y = (p1.y + p2.y) / 2;
	return c;
}

bool CRectangle::OutOfRange(Point p1, Point p2)
{
	return (p1.y < UI.ToolBarHeight || p1.y > UI.height - UI.StatusBarHeight || p1.x < 0 || p1.x > UI.width || p2.y < UI.ToolBarHeight || p2.y > UI.height - UI.StatusBarHeight || p2.x < 0 || p2.x > UI.width);
}
