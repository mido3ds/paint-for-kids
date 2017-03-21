#ifndef CFIGURE_H
#define CFIGURE_H

#include "../DEFS.h"
#include "../GUI/Output.h"

// Base class for all figures
class CFigure
{
public:
    CFigure();
    CFigure(const CFigure& figure_gfx_info);
    
    void SetSelected(bool s); 
    bool IsSelected() const; 

    virtual void Draw(Output* out_p) const; 

    void ChngDrawClr(color draw_clr); // changes the figure's drawing color
    void ChngFillClr(color filling_clr); // changes the figure's filling color

    void ChngZIndex(int ind);
    void ChngBorderWidth(int width);

    bool IsFilled();
    color GetDrawClr();
    color GetFillClr();
    int GetBorderWidth();
    int GetZIndex();

    /// The following functions should be supported by the figure class
    /// It should be overridden by each inherited figure

    /// Decide the parameters that you should pass to each function

    virtual void Rotate();
    virtual void Resize();
    virtual void Move();	

    virtual void Save(ofstream &out_file);	
    virtual void Load(ifstream &in_file);	

    virtual void PrintInfo(Output* out_p);	// on the status bar

protected:
    int id; // Each figure has an id
    bool selected = false; // true if the figure is selected.

    color draw_clr = BLACK; // Draw color of the figure
    color fill_clr = WHITE; // Fill color of the figure
    bool is_filled = false; // CFigure Filled or not
    int border_width = 1; // Width of figure borders

    int z_index = INT32_MAX; // level of object on window, default to max size of int
};

#endif