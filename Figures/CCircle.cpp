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
	left = right = up = down = p1;
	left.x = p1.x - radius;
	right.x = p1.x + radius;
	up.y = p1.y - radius;
	down.y = p1.y + radius;
	p2 = GetSecondPointFromRadius(radius);
}

bool CCircle::IsRotated()
{
	return is_rotated;
}

bool CCircle::CheckResize(double resize_factor)
{
	int new_radius = radius * resize_factor;
	return (p1.x - new_radius < UI.DrawAreaX || p1.x + new_radius > UI.DrawAreaX + UI.DrawAreaWidth || p1.y - new_radius < UI.DrawAreaY || p1.y + new_radius > UI.DrawAreaY + UI.DrawAreaHeight);
}

void CCircle::Resize(double resize_factor)
{
	radius *= resize_factor;
	p2.x = (int(resize_factor * (p2.x - p1.x)))  +  p1.x;
	p2.y = (int(resize_factor * (p2.y - p1.y)))  +  p1.y;
	left.x = p1.x - radius;
	right.x = p1.x + radius;
	up.y = p1.y - radius;
	down.y = p1.y + radius;
}

void CCircle::Drag(const Point& p, Corners corner)
{
	Point pre_left = left;
	Point pre_right = right;
	Point pre_up = up;
	Point pre_down = down;
	int pre_radius = radius;
	if (corner == CIRC_LEFT)
	{
		radius += left.x - p.x;
		left.x = p.x;
		right.x = p1.x + radius;
		up.y = p1.y - radius;
		down.y = p1.y + radius;
	}
	else if (corner == CIRC_RIGHT)
	{
		radius += p.x - right.x;
		right.x = p.x;
		left.x = p1.x - radius;
		up.y = p1.y - radius;
		down.y = p1.y + radius;
	}
	else if (corner == CIRC_UP)
	{
		radius += up.y - p.y;
		up.y = p.y;
		down.y = p1.y + radius;
		left.x = p1.x - radius;
		right.x = p1.x + radius;
	}
	else if (corner == CIRC_DOWN)
	{
		radius += p.y - down.y;
		down.y = p.y;
		up.y = p1.y - radius;
		left.x = p1.x - radius;
		right.x = p1.x + radius;
	}

	if (radius < 10)
	{
		radius = 10;
		left.x = p1.x - 10;
		right.x = p1.x + 10;
		up.y = p1.y - 10;
		down.y = p1.y + 10;
	}
	else if (IsOutOfRange(p1))
	{
		left = pre_left;
		right = pre_right;
		up = pre_up;
		down = pre_down;
		radius = pre_radius;
	}
}

void CCircle::DragPoints(Output* out_p, const GfxInfo& info) const
{
	out_p->DrawCircle(left, 4, info, false);
	out_p->DrawCircle(right, 4, info, false);
	out_p->DrawCircle(up, 4, info, false);
	out_p->DrawCircle(down, 4, info, false);
}

Point CCircle::CalculateCenter()
{
	return p1;
}

int CCircle::GetRadius() const
{
	return radius;
}

double CCircle::GetArea()
{
	return 3.14*GetRadius()*GetRadius();
}

bool CCircle::IsOutOfRange(Point p1)
{
	return (p1.x - radius < UI.DrawAreaX || p1.x  +  radius > UI.DrawAreaX  +  UI.DrawAreaWidth || p1.y - radius < UI.DrawAreaY || p1.y  +  radius > UI.DrawAreaY  +  UI.DrawAreaHeight);
}

bool CCircle::OutOfRange(int x, int y)
{
	Point tp1, tp2;
	tp1.x = p1.x + x;
	tp1.y = p1.y + y;
	tp2.x = p2.x + x;
	tp2.y = p2.y + y;
	if (IsOutOfRange(tp1)) {
		return true;
	}
	return false;
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

		<< border_width << ' '
		<< is_filled << ' '
		<< is_rotated

		<< '\n';
}

void CCircle::Load(ifstream& in_file)
{
	in_file >> id

		>> p1.x
		>> p1.y

		>> radius

		>> draw_clr.ucRed
		>> draw_clr.ucGreen
		>> draw_clr.ucBlue

		>> fill_clr.ucRed
		>> fill_clr.ucGreen
		>> fill_clr.ucBlue
		
		>> border_width
		>> is_filled
		>> is_rotated;

    p2 = GetSecondPointFromRadius(radius);
}

bool CCircle::IsPointInside(const Point& p) const
{
    float RadiusSquare = pow(p1.x - p2.x, 2)  +  pow(p1.y - p2.y, 2);
    float NewDistance = pow(p.x - p1.x, 2)  +  pow(p.y - p1.y, 2);
    return (NewDistance <= RadiusSquare);
}

void CCircle::Move(int x, int y)
{
    Point tp1, tp2;
    tp1.x = p1.x  +  x;
    tp1.y = p1.y  +  y;
    tp2.x = p2.x  +  x;
    tp2.y = p2.y  +  y;
	if (!IsOutOfRange(tp1)) {
		p1 = tp1;
		p2 = tp2;
	}
    
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
		p1.x = rand() % (((UI.width - 5) - ((UI.width / 2) + 5)) + 1) + ((UI.width / 2) + 5);
		p1.y = rand() % (((UI.StatusBarY - 5) - 55) + 1) + 55;

		left.x = p1.x - radius;
		left.y = p1.y;

		right.x = p1.x + radius;
		right.y = p1.y;

		down.x = p1.x;
		down.y = p1.y + radius;

		up.x = p1.x;
		up.y = p1.y - radius;

		p2 = left;

	} while (OutOfRightRange(p1) || OutOfRightRange(left) || OutOfRightRange(right) || OutOfRightRange(up) || OutOfRightRange(down));
}
Corners CCircle::GetCornerPoint(const Point& p) const
{
	if (((p.x - left.x) >= -4 && (p.x - left.x) <= 4) && ((p.y - left.y) >= -4 && (p.y - left.y) <= 4))
		return CIRC_LEFT;
	else if (((p.x - right.x) >= -4 && (p.x - right.x) <= 4) && ((p.y - right.y) >= -4 && (p.y - right.y) <= 4))
		return CIRC_RIGHT;
	else if (((p.x - up.x) >= -4 && (p.x - up.x) <= 4) && ((p.y - up.y) >= -4 && (p.y - up.y) <= 4))
		return CIRC_UP;
	else if (((p.x - down.x) >= -4 && (p.x - down.x) <= 4) && ((p.y - down.y) >= -4 && (p.y - down.y) <= 4))
		return CIRC_DOWN;
	else
		return INVALID;
}

void CCircle::SetAll(CFigure* fig)
{
	CCircle* circ;
	if ((circ = dynamic_cast<CCircle*>(fig)) == nullptr)
		return;

	this->border_width = circ->border_width;
	this->draw_clr = circ->draw_clr;
	this->fill_clr = circ->fill_clr;
	this->is_filled = circ->is_filled;

	SetSelected(circ->IsSelected());
	SetId(circ->GetId());

	this->p1 = circ->p1;
	this->p2 = circ->p2;
	this->radius = circ->radius;
	this->left = circ->left;
	this->right = circ->right;
	this->up = circ->up;
	this->down = circ->down;
}