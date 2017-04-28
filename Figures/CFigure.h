#ifndef CFIGURE_H
#define CFIGURE_H

#include "../DEFS.h"
#include "../GUI/Output.h"
#include <fstream>

// Base class for all figures
class CFigure : public GfxInfo {
public:
	CFigure();
	CFigure(const GfxInfo& figure_gfx_info);

	void SetSelected(bool s);
	bool IsSelected() const;

	void SetId(unsigned int id);
	unsigned int GetId();

    virtual void Draw(Output* out_p) const = 0;
    virtual bool PointCheck(Point p) const = 0;
    void ChngDrawClr(color draw_clr); // changes the figure's drawing color
    void ChngFillClr(color filling_clr); // changes the figure's filling color
    void ChngBorderWidth(int BW); // Changes Border Width
    void ChngZindex(int Z); // Changes Z_Index

    virtual void Rotate(int deg) = 0;
    virtual bool Move(int x, int y) = 0;
    virtual CFigure* Copy() = 0;
    virtual void Save(ofstream& out_file) = 0;
    virtual void Load(ifstream& in_file) = 0;
    virtual Point CalcCenter() = 0;
    virtual void Rotated(bool r) = 0;
    virtual bool IsRotate() = 0;
	virtual void Resize(double resize_factor) = 0;


	//virtual void PrintInfo(Output* out_p) = 0;	// on the status bar

protected:
    unsigned int id; // Each figure has an id
    bool selected = false; // true if the figure is selected.
    bool rotate = false;
};

struct CmpFigures {
	// used to compare figures based on z_index (made for set)
	// lower z_index is put first
	bool operator()(const CFigure* const lhs, const CFigure* const rhs) const
	{
		return lhs->z_index < rhs->z_index;
	}
};

#endif