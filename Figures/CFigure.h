#ifndef CFIGURE_H
#define CFIGURE_H

#include "../DEFS.h"
#include "../GUI/Output.h"
#include <fstream>
#include <ctime>

class CFigure : protected GfxInfo 
{
public:
	CFigure();
	CFigure(const GfxInfo& figure_gfx_info);

	void SetSelected(bool s);
	bool IsSelected() const;

	void SetId(unsigned int id);
	unsigned int GetId() const;

	virtual string GetType() = 0;

	virtual double GetArea() = 0;

    virtual void Draw(Output* out_p) const = 0;
    virtual bool IsPointInside(Point p) const = 0;

    void SetDrawColor(color draw_clr); // changes the figure's drawing color
    void SetFillColor(color filling_clr); // changes the figure's filling color
    void SetBorderWidth(int BW); // Changes Border Width

    color GetDrawColor() const;
    color GetFillColor() const;
    int GetBorderWidth() const;
    bool IsFilled() const;
	bool OutOfRightRange(const Point& p) const;

    virtual void Rotate(int deg) = 0;
    virtual void SetRotated(bool r) = 0;
    virtual bool IsRotated() = 0; 

    virtual void Save(ofstream& out_file) = 0;
    virtual void Load(ifstream& in_file) = 0;

    virtual CFigure* Copy() = 0;
    virtual Point CalculateCenter() = 0;

    virtual void RandomizePosition() = 0; // put object in random valid postion, no change to size
	virtual void Resize(double resize_factor) = 0;

    virtual bool Move(int x, int y) = 0;
    virtual void MoveToLeftSide() = 0; // side for ScrambleAndFind mode
    virtual void MoveToRightSide() = 0; // side for ScrambleAndFind mode
    virtual void PrintInfo(Output* out_p) = 0; // on the status bar

protected:
    unsigned int id; // Each figure has an id
    bool selected = false; // true if the figure is selected.
    bool is_rotated = false;
};

#endif