#ifndef __CCircle_h__
#define __CCircle_h__

#include "CFigure.h"
#include <cmath>

class CCircle : public CFigure {
public:
	CCircle();
	CCircle(Point p1, Point p2, GfxInfo circ_gfx_info);

    virtual void Draw(Output* out_p) const;
    virtual bool PointCheck(Point p) const;
    virtual void Rotate(int deg);
    virtual void Rotated(bool r);
    virtual void Save(ofstream& out_file);
    virtual void Load(ifstream& in_file);
    virtual bool Move(int x, int y);
    virtual CFigure* Copy();
    double GetRadius();
    virtual bool IsRotate();

    virtual Point CalcCenter();

	virtual void Resize(double resize_factor);

	bool OutOfRange(Point p1);

	virtual void PrintInfo(Output* out_p) ;

private:
	// TODO: make it one point and the radius, then del GetRadius and GetSecon....
	Point p1, p2;

	// given radius and this point, return another point
	// another point is (p.x, p.y + rad)
	Point GetSecondPointFromRadius(double rad);
};

#endif /* __CCircle_h__ */