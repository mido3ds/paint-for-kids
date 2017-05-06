#ifndef __CLine_h__
#define __CLine_h__

#include "CFigure.h"

class CLine : public CFigure {
public:
	CLine();
	CLine(Point p1, Point p2, GfxInfo line_gfx_info);

    virtual void Draw(Output* out_p) const;
    virtual bool IsPointInside(Point p) const;
    virtual void Rotate(int deg);
    virtual void SetRotated(bool r);
    virtual bool IsRotated();
    virtual void Save(ofstream& out_file);
    virtual void Load(ifstream& in_file);
    virtual bool Move(int x, int y);
    virtual void MoveToLeftSide();
    virtual void MoveToRightSide();
    virtual void RandomizePosition();
    virtual CFigure* Copy();

	virtual string GetType();
	virtual double GetArea();
	virtual Point CalculateCenter();
	virtual void Resize(double resize_factor);

	bool IsOutOfRange(Point p1, Point p2);

	virtual void PrintInfo(Output* out_p);

	void SetPoints(Point p1, Point p2);

private:
	Point p1, p2;
	const string type = "Line";
};

#endif /* __CLine_h__ */