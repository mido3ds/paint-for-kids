#ifndef __CCircle_h__
#define __CCircle_h__

#include "CFigure.h"
#include <cmath>

class CCircle : public CFigure {
public:
	CCircle();
	CCircle(Point p1, int radius, GfxInfo circ_gfx_info);

    virtual void Draw(Output* out_p) const;
    virtual bool IsPointInside(Point p) const;
    virtual void Rotate(int deg);
    virtual void SetRotated(bool r);
    virtual void Save(ofstream& out_file);
    virtual void Load(ifstream& in_file);
    virtual bool Move(int x, int y);
    virtual void MoveToLeftSide();
    virtual void MoveToRightSide();
    virtual void RandomizePosition();
    virtual void ChangeCenter(const Point& p);
    virtual bool IsPointCorner(const Point& p) const;
    virtual CFigure* Copy();
    virtual bool IsRotated();
    int GetRadius() const;

	virtual string GetType();
	virtual double GetArea();
    virtual Point CalculateCenter();

	virtual void Resize(double resize_factor);

	bool IsOutOfRange(Point p1);

	virtual void PrintInfo(Output* out_p) ;

private:
	Point p1, p2;
    int radius;
	const string type = "Circle";

	// given radius and this point, return another point
	// another point is (p.x, p.y + rad)
	Point GetSecondPointFromRadius(double rad);
};

#endif /* __CCircle_h__ */