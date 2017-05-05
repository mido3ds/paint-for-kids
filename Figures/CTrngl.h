#ifndef __CTrngl_h__
#define __CTrngl_h__

#include "CFigure.h"
#include "Trigonometry.h"

class CTrngl : public CFigure {

public:
	CTrngl();
	CTrngl(Point p1, Point p2, Point p3, GfxInfo trngl_gfx_info);

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
    virtual Point CalculateCenter();
	virtual void Resize(double resize_factor);

	bool IsOutOfRange(Point p1, Point p2, Point p3);

	virtual void PrintInfo(Output* out_p);

private:
	Point p1, p2, p3;
};

#endif /* __CTrngl_h__ */