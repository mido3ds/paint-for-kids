#ifndef CFIGURE_H
#define CFIGURE_H

#include "../DEFS.h"
#include "../GUI/Output.h"

// Base class for all figures
class Figure : protected GfxInfo 
{
public:
    Figure::Figure(const GfxInfo& figure_gfx_info);
    Figure(color draw_clr, color fill_clr, bool is_filled, int border_width,
        int z_index);
    void SetSelected(bool s); // select/unselect the figure
    bool IsSelected() const; // check whether fig is selected

    virtual void Draw(Output* out_p) const = 0; // Draw the figure

    void ChngDrawClr(color draw_clr); // changes the figure's drawing color
    void ChngFillClr(color filling_clr); // changes the figure's filling color

    /// The following functions should be supported by the figure class
    /// It should be overridden by each inherited figure

    /// Decide the parameters that you should pass to each function

    // virtual void Rotate() = 0;	//Rotate the figure
    // virtual void Resize() = 0;	//Resize the figure
    // virtual void Move() = 0;		//Move the figure

    // virtual void Save(ofstream &out_file) = 0;	//Save the figure parameters
    // to the file
    // virtual void Load(ifstream &in_file) = 0;	//Load the figure parameters to
    // the file

    // virtual void PrintInfo(Output* out_p) = 0;	//print all figure info on the
    // status bar

protected:
    int id; // Each figure has an id
    bool selected = false; // true if the figure is selected.

    /// Add more parameters if needed.
};

#endif