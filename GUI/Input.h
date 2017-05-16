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

    ActionType GetUserAction(); // Read the user click and map to an action

	string GetString(Output* pO) const; // Returns a string entered by the user
    color GetColor(int ix, int iy);

    Point GetLastClickedPoint() const; // return last stored point that user clicked on
	clicktype GetClick(int& x, int& y) const; // Get coordinate where user clicks

	Point GetMouseCoord() const; // current coordinates, regardless of clicking or not
	bool IsMouseDown(button btn_state,int &x,int &y) const;  // button maybe LEFT_BUTTON or RIGHT_BUTTON
	clicktype WaitMouseClick(int &iX, int &iY);
private:
	window* wind_p; // Pointer to the Graphics Window
	Point last_click;
};

#endif