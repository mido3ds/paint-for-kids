#ifndef CFIGURE_H
#define CFIGURE_H

#include "../DEFS.h"
#include "../GUI/Output.h"
#include <fstream>

class CFigure : protected GfxInfo 
{
public:
	CFigure();
	CFigure(const GfxInfo& figure_gfx_info);

	void SetSelected(bool s);
	bool IsSelected() const;

	void SetId(unsigned int id);
	unsigned int GetId() const;

    virtual void Draw(Output* out_p) const = 0;
    virtual bool PointCheck(Point p) const = 0;

    void SetDrawClr(color draw_clr); // changes the figure's drawing color
    void SetFillClr(color filling_clr); // changes the figure's filling color
    void SetBorderWidth(int BW); // Changes Border Width

    color GetDrawClr() const; // TODO: rename every clr to color
    color GetFillClr() const;
    int GetBorderWidth() const;
    bool IsFilled() const;

    virtual void Rotate(int deg) = 0;
    virtual bool Move(int x, int y) = 0;
    virtual CFigure* Copy() = 0;
    virtual void Save(ofstream& out_file) = 0;
    virtual void Load(ifstream& in_file) = 0;
    virtual Point CalcCenter() = 0;
    virtual void Rotated(bool r) = 0; // TODO: rename to SetRotated
    virtual bool IsRotate() = 0; // TODO: rename to IsRotated
	virtual void Resize(double resize_factor) = 0;
    virtual void MoveToLeftSide() = 0; // side for ScrambleAndFind mode


	virtual void PrintInfo(Output* out_p) = 0;	// on the status bar

protected:
    unsigned int id; // Each figure has an id
    bool selected = false; // true if the figure is selected.
    bool rotate = false;
};

#endif