#ifndef __CLine_h__
#define __CLine_h__

#include "CFigure.h"

class CLine : public CFigure {
public:
	CLine();
	CLine(Point p1, Point p2, GfxInfo line_gfx_info);

    virtual void Draw(Output* out_p) const;
    virtual bool PointCheck(Point p) const;
    virtual void Rotate(int deg);
    virtual void Rotated(bool r);
    virtual bool IsRotate();
    virtual void Save(ofstream& out_file);
    virtual void Load(ifstream& in_file);
    virtual bool Move(int x, int y);
    virtual CFigure* Copy();

	virtual Point CalcCenter();
	virtual void Resize(double resize_factor);

	bool OutOfRange(Point p1, Point p2);

	Point p1, p2;
};

#endif /* __CLine_h__ */