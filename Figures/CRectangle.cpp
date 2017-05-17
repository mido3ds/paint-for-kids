#include "CRectangle.h"

CRectangle::CRectangle(Point p1, Point p2, GfxInfo figure_gfx_info)
	: CFigure(figure_gfx_info)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = { p1.x, p2.y };
	this->p4 = { p2.x, p1.y };
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
void CRectangle::SetRotated(bool r)
{
	is_rotated = r;
}
bool CRectangle::IsRotated()
{
	return is_rotated;
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

		<< border_width

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
		>> fill_clr.ucBlue
		
		>>border_width;
}

bool CRectangle::CheckResize(double resize_factor)
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

void CRectangle::Resize(double resize_factor)
{
	Point c = CalculateCenter();
	p1.x = (int(resize_factor * (p1.x - c.x))) + c.x;
	p1.y = (int(resize_factor * (p1.y - c.y))) + c.y;
	p2.x = (int(resize_factor * (p2.x - c.x))) + c.x;
	p2.y = (int(resize_factor * (p2.y - c.y))) + c.y;
	p3 = { p1.x, p2.y };
	p4 = { p2.x, p1.y };
}

void CRectangle::Drag(const Point& p, Corners corner)
{
	Point pre_p1 = p1;
	Point pre_p2 = p2;
	if (corner == RECT_1)
	{
		p1 = p;
		p3.x = p.x;
		p4.y = p.y;
	}
	else if (corner == RECT_2)
	{
		p2 = p;
		p4.x = p.x;
		p3.y = p.y;
	}
	else if (corner == RECT_3)
	{
		p3 = p;
		p1.x = p.x;
		p2.y = p.y;
	}
	else if (corner == RECT_4)
	{
		p4 = p;
		p1.y = p.y;
		p2.x = p.x;
	}
	if (IsOutOfRange(p1, p2))
	{
		p1 = pre_p1;
		p2 = pre_p2;
		p3 = { p1.x, p2.y };
		p4 = { p2.x, p1.y };
	}
}

void CRectangle::DragPoints(Output* out_p, const GfxInfo& info) const
{
	out_p->DrawCircle(p1, 4, info, false);
	out_p->DrawCircle(p2, 4, info, false);
	out_p->DrawCircle(p3, 4, info, false);
	out_p->DrawCircle(p4, 4, info, false);
}

Point CRectangle::CalculateCenter()
{
	Point c;
	c.x = (p1.x + p2.x) / 2;
	c.y = (p1.y + p2.y) / 2;
	return c;
}

bool CRectangle::IsPointInside(const Point& p) const
{
	bool t1 = false;
	bool t2 = false;

	if (p1.x > p2.x)
		t1 = (p.x >= p2.x) && (p.x <= p1.x);
	else
		t1 = (p.x >= p1.x) && (p.x <= p2.x);

	if (p1.y > p2.y)
		t2 = (p.y >= p2.y) && (p.y <= p1.y);
	else
		t2 = (p.y >= p1.y) && (p.y <= p2.y);
	return (t1 && t2);
}

bool CRectangle::Move(int x, int y)
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

CFigure* CRectangle::Copy()
{
    GfxInfo c;
    c.border_width = this->border_width;
    c.draw_clr = this->draw_clr;
    c.fill_clr = this->fill_clr;
    c.is_filled = this->is_filled;

    CFigure* copy = new CRectangle(p1, p2, c);

	copy->SetSelected(this->IsSelected());
	copy->SetId(this->GetId());
	
    return copy;
}

string CRectangle::GetType()
{
	return type;
}

double CRectangle::GetArea()
{
	double length = abs(p1.x - p2.x);
	double width = abs(p1.y - p2.y);
	return length*width;
}

bool CRectangle::IsOutOfRange(Point p1, Point p2)
{
	return (p1.y < UI.DrawAreaY || p1.y > UI.DrawAreaY + UI.DrawAreaHeight || p1.x < UI.DrawAreaX || p1.x > UI.DrawAreaX + UI.DrawAreaWidth || p2.y < UI.DrawAreaY || p2.y > UI.DrawAreaY + UI.DrawAreaHeight || p2.x < UI.DrawAreaX || p2.x > UI.DrawAreaX + UI.DrawAreaWidth);
}

void CRectangle::PrintInfo(Output* out_p)
{
	int width = abs(p1.x-p2.x);
	int height = abs(p1.y - p2.y);
	out_p->PrintMessage("Rectangle... ID:" + to_string(this->GetId()) + " Height: "+to_string(height)+" Width: "+to_string(width), WHITE, true);
}

void CRectangle::MoveToLeftSide()
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

void CRectangle::RandomizePosition()
{
	Point center = CalculateCenter();

	// get difference between center and points
	Point def1(p1.x - center.x, p1.y - center.y);
	Point def2(p2.x - center.x, p2.y - center.y);
	do
	{
		center.x = rand() % (((UI.width - 5) - ((UI.width / 2) + 5)) + 1) + ((UI.width / 2) + 5);
		center.y = rand() % (((UI.StatusBarY - 5) - 55) + 1) + 55;
		p1 = center + def1;
		p2 = center + def2;
	} while (OutOfRightRange(p1) || OutOfRightRange(p2));
}

Corners CRectangle::GetCornerPoint(const Point& p) const
{
	if (((p.x - p1.x) >= -4 && (p.x - p1.x) <= 4) && ((p.y - p1.y) >= -4 && (p.y - p1.y) <= 4))
		return RECT_1;
	else if (((p.x - p2.x) >= -4 && (p.x - p2.x) <= 4) && ((p.y - p2.y) >= -4 && (p.y - p2.y) <= 4))
		return RECT_2;
	else if (((p.x - p3.x) >= -4 && (p.x - p3.x) <= 4) && ((p.y - p3.y) >= -4 && (p.y - p3.y) <= 4))
		return RECT_3;
	else if (((p.x - p4.x) >= -4 && (p.x - p4.x) <= 4) && ((p.y - p4.y) >= -4 && (p.y - p4.y) <= 4))
		return RECT_4;
	else
		return INVALID;
}

void CRectangle::SetAll(CFigure* fig)
{
	CRectangle* rect;
	if ((rect = dynamic_cast<CRectangle*>(fig)) == nullptr)
		return;

	this->border_width = rect->border_width;
	this->draw_clr = rect->draw_clr;
	this->fill_clr = rect->fill_clr;
	this->is_filled = rect->is_filled;

	SetSelected(rect->IsSelected());
	SetId(rect->GetId());

	this->p1 = rect->p1;
	this->p2 = rect->p2;
	this->p3 = rect->p3;
	this->p4 = rect->p4;

}