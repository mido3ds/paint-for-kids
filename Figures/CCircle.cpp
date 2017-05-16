#include "CCircle.h"

CCircle::CCircle()
	:radius(0)
{
}

CCircle::CCircle(Point p1, int radius, GfxInfo circ_gfx_info)
	: CFigure(circ_gfx_info)
{
	this->p1 = p1;
	this->radius = radius;

	p2 = GetSecondPointFromRadius(radius);
}

bool CCircle::IsRotated()
{
	return is_rotated;
}

void CCircle::Resize(double resize_factor)
{
	p2.x = (int(resize_factor * (p2.x - p1.x)))  +  p1.x;
	p2.y = (int(resize_factor * (p2.y - p1.y)))  +  p1.y;
	radius = sqrt(pow((p1.y - p2.y), 2) + pow((p1.x - p2.x), 2));
}

Point CCircle::CalculateCenter()
{
	return p1;
}

int CCircle::GetRadius() const
{
	return radius;
}

string CCircle::GetType()
{
	return type;
}

double CCircle::GetArea()
{
	return 3.14*GetRadius()*GetRadius();
}

bool CCircle::IsOutOfRange(Point p1)
{
	return (p1.x - radius < UI.DrawAreaX || p1.x  +  radius > UI.DrawAreaX  +  UI.DrawAreaWidth || p1.y - radius < UI.DrawAreaY || p1.y  +  radius > UI.DrawAreaY  +  UI.DrawAreaHeight);
}

Point CCircle::GetSecondPointFromRadius(double rad)
{
	return Point(p1.x, p1.y  +  rad);
}

void CCircle::Draw(Output* out_p) const
{
	out_p->DrawCircle(p1, radius, *this, selected);
}

void CCircle::Rotate(int deg)
{
}

void CCircle::SetRotated(bool r)
{
	is_rotated = r;
}


void CCircle::Save(ofstream& out_file)
{
	out_file << "CIRCLE" << ' '
		<< id << ' '

		<< p1.x << ' '
		<< p1.y << ' '

		<< radius << ' '

		<< draw_clr.ucRed << ' '
		<< draw_clr.ucGreen << ' '
		<< draw_clr.ucBlue << ' '

		<< fill_clr.ucRed << ' '
		<< fill_clr.ucGreen << ' '
		<< fill_clr.ucBlue << ' '

		<< border_width

		<< '\n';
}

void CCircle::Load(ifstream& in_file)
{
	double rad;
	in_file >> id

		>> p1.x
		>> p1.y

		>> rad

		>> draw_clr.ucRed
		>> draw_clr.ucGreen
		>> draw_clr.ucBlue

		>> fill_clr.ucRed
		>> fill_clr.ucGreen
		>> fill_clr.ucBlue
		
		>> border_width;

    p2 = GetSecondPointFromRadius(rad);
}

bool CCircle::IsPointInside(const Point& p) const
{
    float RadiusSquare = pow(p1.x - p2.x, 2)  +  pow(p1.y - p2.y, 2);
    float NewDistance = pow(p.x - p1.x, 2)  +  pow(p.y - p1.y, 2);
    return (NewDistance <= RadiusSquare);
}

bool CCircle::Move(int x, int y)
{
    Point tp1, tp2;
    tp1.x = p1.x  +  x;
    tp1.y = p1.y  +  y;
    tp2.x = p2.x  +  x;
    tp2.y = p2.y  +  y;
    if (!IsOutOfRange(p1)) {
        p1 = tp1;
        p2 = tp2;
        return true;
    }
    return false;
}

CFigure* CCircle::Copy()
{
    GfxInfo c;
    c.border_width = this->border_width;
    c.draw_clr = this->draw_clr;
    c.fill_clr = this->fill_clr;
    c.is_filled = this->is_filled;

    CFigure* copy = new CCircle(p1, radius, c);

	copy->SetSelected(this->IsSelected());
	copy->SetId(this->GetId());
	
    return copy;
}

void CCircle::PrintInfo(Output* out_p)
{
	out_p->PrintMessage("Circle...ID:" + to_string(this->GetId()) + "Center:(" + to_string(p1.x) + "," + to_string(p1.y) + ") Radius:" + to_string(radius), WHITE, true);
}

void CCircle::MoveToLeftSide()
{
	p1.x /= 2;
}

void CCircle::RandomizePosition()
{
	Point left;
	Point right;
	Point up;
	Point down;

	do
	{
		p1.x = rand() % (((UI.width-5) - ((UI.width / 2)+5)) + 1) + ((UI.width / 2)+5);
		p1.y = rand() % (((UI.StatusBarY-5) - 55) + 1) + 55;

		left.x = p1.x - radius;
		left.y = p1.y;

		right.x = p1.x + radius;
		right.y = p1.y;

		down.x = p1.x;
		down.y = p1.y + radius;

		up.x = p1.x;
		up.y = p1.y - radius;

	} while (OutOfRightRange(p1) || OutOfRightRange(left) || OutOfRightRange(right) || OutOfRightRange(up) || OutOfRightRange(down));
}

//void CCircle::ChangeCenter(const Point& p)
//{
//	// TODO
//}
//
//bool CCircle::IsPointCorner(const Point& p) const
//{
//	// TODO
//	return true;
//}
//
//Point& CCircle::GetCornerPoint(const Point& p)
//{
//	// TODO
//	return p1;
//}