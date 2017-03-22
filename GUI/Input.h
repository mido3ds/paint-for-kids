#ifndef INPUT_H
#define INPUT_H

#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../DEFS.h"
#include "UI_Info.h"

class Output;
class Input // The application manager should have a pointer to this class
{
public:
    Input(window* pW); // Consturctor
    ~Input();

    void GetPointClicked(int& x, int& y) const; // Get coordinate where user clicks
    string GetSrting(Output* pO) const; // Returns a string entered by the user

    ActionType GetUserAction() const; // Read the user click and map to an action

private:
    window* wind_p; // Pointer to the Graphics Window
};

#endif