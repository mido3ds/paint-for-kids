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

    //Read 1st corner and store in point p1
    in_p->GetPointClicked(p1.x, p1.y);

    out_p->PrintMessage("New Line: Click at second corner");

    //Read 2nd corner and store in point p2
    in_p->GetPointClicked(p2.x, p2.y);

    gfx.is_filled = false; //default is not filled
    //get drawing, filling colors and pen width from the interface
    gfx.draw_clr = out_p->GetCrntDrawColor();
    gfx.fill_clr = out_p->GetCrntFillColor();
    gfx.border_width = out_p->GetCrntPenWidth();

    out_p->ClearStatusBar();
    out_p->ClearTToolBar();

    id = manager_p->GenerateNextId();
}

//Execute the action
void AddLineAction::Execute()
{
    //Add the lineangle to the list of figures
    line = new CLine(p1, p2, gfx);
    line->SetId(id);
    if (!line->OutOfRange(p1, p2)) {
        manager_p->AddFigure(line);
    } else {
        manager_p->GetOutput()->PrintMessage("The Line Is Out Of Range");
    }
}

void AddLineAction::Undo()
{
    manager_p->DeleteFigure(id);
}
