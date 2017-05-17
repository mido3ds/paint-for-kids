#ifndef CFIGURE_H
#define CFIGURE_H

#include "../DEFS.h"
#include "../GUI/Output.h"
#include <fstream>
#include <ctime>

enum class PointState 
{
	CORNER, 
	INSIDE, 
	OUTSIDE
};

//figures corners that could be dragged
enum Corners
{
	RECT_1,
	RECT_2,
	RECT_3,
	RECT_4,
	CIRC_LEFT,
	CIRC_RIGHT,
	CIRC_UP,
	CIRC_DOWN,
	LINE_1,
	LINE_2,
	TRNGL_1,
	TRNGL_2,
	TRNGL_3,
	INVALID
};

class CFigure : protected GfxInfo 
{
public:
	CFigure();
	CFigure(const GfxInfo& figure_gfx_info);

    virtual void Draw(Output* out_p) const = 0;

	void SetSelected(bool s);
	bool IsSelected() const;

	void SetId(unsigned int id);
	unsigned int GetId() const;

	virtual string GetType() = 0;
	virtual double GetArea() = 0;

    virtual bool IsPointInside(const Point& p) const = 0;

    void SetDrawColor(color draw_clr);
    void SetFillColor(color filling_clr); 
    void SetBorderWidth(int border_width); 

    color GetDrawColor() const;
    color GetFillColor() const;
    int GetBorderWidth() const;
    bool IsFilled() const;
	bool OutOfDrawingArea(const Point& p) const;
	bool OutOfRightRange(const Point& p) const;

    virtual void Rotate(int deg) = 0;
    virtual void SetRotated(bool r) = 0;
    virtual bool IsRotated() = 0; 

    virtual void Save(ofstream& out_file) = 0;
    virtual void Load(ifstream& in_file) = 0;

    virtual CFigure* Copy() = 0;

    virtual void RandomizePosition() = 0; // put object in random valid postion, no change to size
	virtual void Resize(double resize_factor) = 0;
	virtual bool CheckResize(double resize_factor) = 0;
	virtual void Drag(const Point& p, Corners corner) = 0;
	virtual void DragPoints(Output* out_p, const GfxInfo& info) const = 0;
	virtual Corners GetCornerPoint(const Point& p) const = 0; // get nearest corner point

    virtual bool Move(int x, int y) = 0;
    virtual void MoveToLeftSide() = 0;

    virtual Point CalculateCenter() = 0;

    virtual void PrintInfo(Output* out_p) = 0; // on the status bar
	virtual void SetAll(CFigure*) = 0;

protected:
    unsigned int id; // Each figure has an id
    bool selected = false; // true if the figure is selected.
    bool is_rotated = false;
};

#endif