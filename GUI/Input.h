#ifndef INPUT_H
#define INPUT_H

#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../DEFS.h"
#include "UI_Info.h"
#include <fstream>
using namespace std;

class Output;
class Input // The application manager should have a pointer to this class
{
public:
	Input(window* pW); // Consturctor
	~Input();

	clicktype GetPointClicked(int& x, int& y); // Get coordinate where user clicks
	string GetString(Output* pO) const; // Returns a string entered by the user

    color PickColor(int ix, int iy);

    ActionType GetUserAction() const; // Read the user click and map to an action
    Point GetClickedPoint() const; // return last stored point that user clicked on

private:
	window* wind_p; // Pointer to the Graphics Window
	Point last_click;
};

#endif