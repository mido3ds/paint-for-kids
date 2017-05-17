#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"
#include <cmath>

class CRectangle : public CFigure {

public:
	CRectangle();
	CRectangle(Point, Point, GfxInfo figure_gfx_info);

    virtual void Draw(Output* out_p) const;
    virtual bool IsPointInside(const Point& p) const;
    virtual void Rotate(int deg);
    virtual void SetRotated(bool r);
    virtual bool IsRotated();
    virtual void Save(ofstream& out_file);
    virtual void Load(ifstream& in_file);
    virtual bool Move(int x, int y);
    virtual void MoveToLeftSide();
    virtual void RandomizePosition();
    virtual CFigure* Copy();

	virtual string GetType();
	virtual double GetArea();
	virtual Point CalculateCenter();
	virtual void Resize(double resize_factor);
	virtual bool CheckResize(double resize_factor);
	virtual void Drag(const Point& p, Corners corner);
	virtual void DragPoints(Output* out_p, const GfxInfo& info) const;
	virtual Corners GetCornerPoint(const Point& p) const; // get nearest corner point

	bool IsOutOfRange(Point p1, Point p2);

	virtual void PrintInfo(Output* out_p);
	virtual void SetAll(CFigure*);

private:
	Point p1, p2, p3, p4;
	
	const string type = "Rectangle";
};

#endif