#include "AddLineAction.h"

AddLineAction::AddLineAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void AddLineAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("New Line: Click at first point");

    line = new CLine();

    //Read 1st corner and store in point p1
    in_p->GetPointClicked(line->p1.x, line->p1.y);

    out_p->PrintMessage("New Line: Click at second corner");

    //Read 2nd corner and store in point p2
    in_p->GetPointClicked(line->p2.x, line->p2.y);

    line->is_filled = false; //default is not filled
    //get drawing, filling colors and pen width from the interface
    line->draw_clr = out_p->GetCrntDrawColor();
    line->fill_clr = out_p->GetCrntFillColor();
    line->border_width = out_p->GetCrntPenWidth();

    out_p->ClearStatusBar();
}

//Execute the action
void AddLineAction::Execute()
{
    //Add the lineangle to the list of figures
    manager_p->AddFigure(line);
}
