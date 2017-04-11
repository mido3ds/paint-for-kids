#include "AddRectAction.h"

AddRectAction::AddRectAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void AddRectAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("New Rectangle: Click at first corner");

    rect = new CRectangle();

    //Read 1st corner and store in point p1
    in_p->GetPointClicked(rect->p1.x, rect->p1.y);

    out_p->PrintMessage("New Rectangle: Click at second corner");

    //Read 2nd corner and store in point p2
    in_p->GetPointClicked(rect->p2.x, rect->p2.y);

    rect->is_filled = false; //default is not filled
    //get drawing, filling colors and pen width from the interface
    rect->draw_clr = out_p->GetCrntDrawColor();
    rect->fill_clr = out_p->GetCrntFillColor();
    rect->border_width = out_p->GetCrntPenWidth();

    out_p->ClearStatusBar();

    id = manager_p->GenerateNextId();
    rect->SetId(id);
}

//Execute the action
void AddRectAction::Execute()
{
    //Add the lineangle to the list of figures
    manager_p->AddFigure(rect);
}

void AddRectAction::Undo()
{
    
}