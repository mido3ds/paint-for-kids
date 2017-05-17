#ifndef __CCircle_h__
#define __CCircle_h__

#include "CFigure.h"
#include <cmath>

class CCircle : public CFigure {
public:
	CCircle();
	CCircle(Point p1, int radius, GfxInfo circ_gfx_info);

    virtual void Draw(Output* out_p) const;
    virtual bool IsPointInside(const Point& p) const;
    virtual void Rotate(int deg);
    virtual void SetRotated(bool r);
    virtual void Save(ofstream& out_file);
    virtual void Load(ifstream& in_file);
    virtual bool Move(int x, int y);
    virtual void MoveToLeftSide();
    virtual void RandomizePosition();
    virtual CFigure* Copy();
    virtual bool IsRotated();
    int GetRadius() const;

	virtual string GetType();
	virtual double GetArea();
    virtual Point CalculateCenter();

	virtual void Resize(double resize_factor);
	virtual bool CheckResize(double resize_factor);
	virtual void Drag(const Point& p, Corners corner);
	virtual void DragPoints(Output* out_p, const GfxInfo& info) const;
	virtual Corners GetCornerPoint(const Point& p) const; // get nearest corner point

	bool IsOutOfRange(Point p1);

	virtual void PrintInfo(Output* out_p) ;
	virtual void SetAll(CFigure*);

private:
	Point p1, p2;
	Point left;
	Point right;
	Point up;
	Point down;
    int radius;
	const string type = "Circle";

	// given radius and this point, return another point
	// another point is (p.x, p.y + rad)
	Point GetSecondPointFromRadius(double rad);
};

#endif /* __CCircle_h__ */