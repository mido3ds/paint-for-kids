#include "AddRectAction.h"
#include "../Figures/Rectangle.h"

#include "../ApplicationManager.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

AddRectAction::AddRectAction(ApplicationManager* app_p)
    : Action(app_p)
{}

void AddRectAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("New Rectangle: Click at first corner");

    //Read 1st corner and store in point p1
    in_p->GetPointClicked(p1.x, p1.y);

    out_p->PrintMessage("New Rectangle: Click at second corner");

    //Read 2nd corner and store in point p2
    in_p->GetPointClicked(p2.x, p2.y);

    rect_gfx_info.is_filled = false; //default is not filled
    //get drawing, filling colors and pen width from the interface
    rect_gfx_info.draw_clr = out_p->getCrntDrawColor();
    rect_gfx_info.fill_clr = out_p->getCrntFillColor();
    rect_gfx_info.border_width = out_p->getCrntPenWidth();

    out_p->ClearStatusBar();
}

//Execute the action
void AddRectAction::Execute()
{
    //This action needs to read some parameters first
    ReadActionParameters();

    //Create a rectangle with the parameters read from the user
    Rectangle* R = new Rectangle(p1, p2, rect_gfx_info);

    //Add the rectangle to the list of figures
    manager_p->AddFigure(R);
}
