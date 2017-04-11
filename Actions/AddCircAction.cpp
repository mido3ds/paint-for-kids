#include "AddCircAction.h"

AddCircAction::AddCircAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void AddCircAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("New Circle: Click at first point");

    circ = new CCircle();

    //Read 1st corner and store in point p1
    in_p->GetPointClicked(circ->p1.x, circ->p1.y);

    out_p->PrintMessage("New Circle: Click at second point");

    //Read 2nd corner and store in point p2
    in_p->GetPointClicked(circ->p2.x, circ->p2.y);

    circ->is_filled = false; //default is not filled
    //get drawing, filling colors and pen width from the interface
    circ->draw_clr = out_p->GetCrntDrawColor();
    circ->fill_clr = out_p->GetCrntFillColor();
    circ->border_width = out_p->GetCrntPenWidth();

    out_p->ClearStatusBar();

    id = manager_p->GenerateNextId();
    circ->SetId(id);
}

//Execute the action
void AddCircAction::Execute()
{
    manager_p->AddFigure(circ);
}

void AddCircAction::Undo()
{
    manager_p->DeleteFigure(id);
}
