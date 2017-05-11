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
    virtual void MoveToRightSide();
    virtual void RandomizePosition();
    virtual void ChangeCenter(const Point& p);
    virtual bool IsPointCorner(const Point& p) const;
    virtual Point& GetCornerPoint(const Point& p);
    virtual CFigure* Copy();

	virtual string GetType();
	virtual double GetArea();
	virtual Point CalculateCenter();
	virtual void Resize(double resize_factor);

	bool IsOutOfRange(Point p1, Point p2);

	virtual void PrintInfo(Output* out_p);

private:
	Point p1, p2;
	const string type = "Rectangle";
};

#endif