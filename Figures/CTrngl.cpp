#include "CTrngl.h"

CTrngl::CTrngl()
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
	Point c = CalculateCenter();
	Point temp1 = p1;
	Point temp2 = p2;
	Point temp3 = p3;
	Point temp5 = p3;
	Point temp4;
	Point temp6;
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
	if (IsOutOfRange(temp3, temp4, temp6))
	{
		is_rotated = false;
	}
	else {
		is_rotated = true;
		p1 = temp3;
		p2 = temp4;
		p3 = temp6;
	}
}

void CTrngl::SetRotated(bool r)
{
	is_rotated = r;
}

bool CTrngl::IsRotated()
{
	return is_rotated;
}

bool CTrngl::CheckResize(double resize_factor)
{
	Point new_p1;
	Point new_p2;
	Point new_p3;
	Point c = CalculateCenter();
	new_p1.x = (int(resize_factor * (p1.x - c.x))) + c.x;
	new_p1.y = (int(resize_factor * (p1.y - c.y))) + c.y;
	new_p2.x = (int(resize_factor * (p2.x - c.x))) + c.x;
	new_p2.y = (int(resize_factor * (p2.y - c.y))) + c.y;
	new_p3.x = (int(resize_factor * (p3.x - c.x))) + c.x;
	new_p3.y = (int(resize_factor * (p3.y - c.y))) + c.y;

	if (IsOutOfRange(new_p1, new_p2, new_p3))
		return false;

	return true;
}

void CTrngl::Resize(double resize_factor)
{
	Point c = CalculateCenter();
	p1.x = (int(resize_factor * (p1.x - c.x))) + c.x;
	p1.y = (int(resize_factor * (p1.y - c.y))) + c.y;
	p2.x = (int(resize_factor * (p2.x - c.x))) + c.x;
	p2.y = (int(resize_factor * (p2.y - c.y))) + c.y;
	p3.x = (int(resize_factor * (p3.x - c.x))) + c.x;
	p3.y = (int(resize_factor * (p3.y - c.y))) + c.y;
}

void CTrngl::Drag(const Point& p, Corners corner)
{
	if (corner == TRNGL_1)
		p1 = p;
	else if (corner == TRNGL_2)
		p2 = p;
	else if (corner == TRNGL_3)
		p3 = p;
}

void CTrngl::DragPoints(Output* out_p, const GfxInfo& info) const
{
	out_p->DrawCircle(p1, 4, info, false);
	out_p->DrawCircle(p2, 4, info, false);
	out_p->DrawCircle(p3, 4, info, false);
}
double CTrngl::GetArea()
{
	return Trigonometry::Area(p1, p2, p3);
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

		<< border_width << ' '
		<< is_filled << ' '
		<< is_rotated

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
		>> fill_clr.ucBlue
		
		>> border_width
		>> is_filled
		>> is_rotated;
}

Point CTrngl::CalculateCenter()
{
	/*From basic geometry the center of the triangle is the intersection
	point of it's midians so the center would be the intersection point
	of two midians*/
	Point c;
	Point pc1((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
	Point pc2((p2.x + p3.x) / 2, (p2.y + p3.y) / 2);
	//Calculating lines slopes
	double m1 = double(pc1.y - p3.y) / (pc1.x - p3.x);
	double m2 = double(pc2.y - p1.y) / (pc2.x - p1.x);
	//solving equations to get the intersection point
	c.x = int((m1*pc1.x - m2*pc2.x + pc2.y - pc1.y) / (m1 - m2));
	c.y = int(m2 * (c.x - pc2.x) + pc2.y);

	return c;
}

bool CTrngl::IsOutOfRange(Point p1, Point p2, Point p3)
{
    return (p1.y < UI.DrawAreaY || p1.y > UI.DrawAreaY + UI.DrawAreaHeight || p1.x < UI.DrawAreaX || p1.x > UI.DrawAreaX + UI.DrawAreaWidth || p2.y < UI.DrawAreaY || p2.y > UI.DrawAreaY + UI.DrawAreaHeight || p2.x < UI.DrawAreaX || p2.x > UI.DrawAreaX + UI.DrawAreaWidth || p3.y < UI.DrawAreaY || p3.y > UI.DrawAreaY + UI.DrawAreaHeight || p3.x < UI.DrawAreaX || p3.x > UI.DrawAreaX + UI.DrawAreaWidth);
}

bool CTrngl::OutOfRange(int x, int y)
{
	Point tp1, tp2, tp3;
	tp1.x = p1.x + x;
	tp1.y = p1.y + y;
	tp2.x = p2.x + x;
	tp2.y = p2.y + y;
	tp3.x = p3.x + x;
	tp3.y = p3.y + y;
	if (IsOutOfRange(tp1, tp2, tp3)) {
		return true;
	}
	return false;
}

bool CTrngl::IsPointInside(const Point& p) const
{
	if ((SameSide(p, p1, p2, p3) && SameSide(p, p2, p1, p3) && SameSide(p, p3, p1, p2)))
		return true;
	else
		return false;
}

void CTrngl::Move(int x, int y)
{
	Point tp1, tp2, tp3;
	tp1.x = p1.x + x;
	tp1.y = p1.y + y;
	tp2.x = p2.x + x;
	tp2.y = p2.y + y;
	tp3.x = p3.x + x;
	tp3.y = p3.y + y;
	if (!IsOutOfRange(tp1, tp2, tp3)) {
		p1 = tp1;
		p2 = tp2;
		p3 = tp3;
	}
}

CFigure* CTrngl::Copy()
{
    GfxInfo c;
    c.border_width = this->border_width;
    c.draw_clr = this->draw_clr;
    c.fill_clr = this->fill_clr;
    c.is_filled = this->is_filled;
	
    CFigure* copy = new CTrngl(p1, p2, p3, c);

	copy->SetSelected(this->IsSelected());
	copy->SetId(this->GetId());
    return copy;
}

void CTrngl::PrintInfo(Output* out_p)
{
	out_p->PrintMessage("Triangle... ID: " + to_string(this->GetId()) + " Corners : (" + to_string(p1.x) + "," + to_string(p1.y) + ") , (" + to_string(p2.x) + "," + to_string(p2.y) + ") , (" + to_string(p3.x) + "," + to_string(p3.y) + ")", WHITE, true);
}

double CTrngl::CrossProduct(Point p1, Point p2) const
{
	return ((p1.x * p2.y) - (p1.y * p2.x));
}

bool CTrngl::SameSide(Point p1, Point p2, Point a, Point b) const
{
	double cp1 = CrossProduct(b - a, p1 - a);
	double cp2 = CrossProduct(b - a, p2 - a);
	double cp12 = cp1 * cp2;
	if (cp12 >= 0)
		return true;
	return false;
}

void CTrngl::MoveToLeftSide()
{
	Point center = CalculateCenter();

	// get difference between center and points
	int def1 = p1.x - center.x;
	int def2 = p2.x - center.x;
	int def3 = p3.x - center.x;

	center.x /= 2;

	// remake the points from the previous centere
	p1.x = center.x + def1;
	p2.x = center.x + def2;
	p3.x = center.x + def3;
}

void CTrngl::RandomizePosition()
{

	Point center = CalculateCenter();

	// get difference between center and points
	Point def1(p1.x - center.x, p1.y - center.y);
	Point def2(p2.x - center.x, p2.y - center.y);
	Point def3(p3.x - center.x, p3.y - center.y);
	do
	{
		center.x = rand() % (((UI.width - 5) - ((UI.width / 2) + 5)) + 1) + ((UI.width / 2) + 5);
		center.y = rand() % (((UI.StatusBarY - 5) - 55) + 1) + 55;
		p1 = center + def1;
		p2 = center + def2;
		p3 = center + def3;
	} while (OutOfRightRange(p1) || OutOfRightRange(p2) || OutOfRightRange(p3));

}

Corners CTrngl::GetCornerPoint(const Point& p) const
{
	if (((p.x - p1.x) >= -4 && (p.x - p1.x) <= 4) && ((p.y - p1.y) >= -4 && (p.y - p1.y) <= 4))
		return TRNGL_1;
	else if (((p.x - p2.x) >= -4 && (p.x - p2.x) <= 4) && ((p.y - p2.y) >= -4 && (p.y - p2.y) <= 4))
		return TRNGL_2;
	else if (((p.x - p3.x) >= -4 && (p.x - p3.x) <= 4) && ((p.y - p3.y) >= -4 && (p.y - p3.y) <= 4))
		return TRNGL_3;
	else
		return INVALID;
}

void CTrngl::SetAll(CFigure* fig)
{
	CTrngl* trngl;
	if ((trngl = dynamic_cast<CTrngl*>(fig)) == nullptr)
		return;

	this->border_width = trngl->border_width;
	this->draw_clr = trngl->draw_clr;
	this->fill_clr = trngl->fill_clr;
	this->is_filled = trngl->is_filled;

	SetSelected(trngl->IsSelected());
	SetId(trngl->GetId());

	this->p1 = trngl->p1;
	this->p2 = trngl->p2;
	this->p3 = trngl->p3;
}