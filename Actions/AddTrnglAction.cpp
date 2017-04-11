#include "AddTrnglAction.h"

AddTrnglAction::AddTrnglAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void AddTrnglAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("New triangle: Click at first point");

    //Read 1st corner and store in point p1
    in_p->GetPointClicked(p1.x, p1.y);

    out_p->PrintMessage("New triangle: Click at second corner");

    //Read 2nd corner and store in point p2
    in_p->GetPointClicked(p2.x, p2.y);

    out_p->PrintMessage("New triangle: Click at third corner");

    //Read 2nd corner and store in point p2
    in_p->GetPointClicked(p3.x, p3.y);

    gfx.is_filled = false; //default is not filled
    //get drawing, filling colors and pen width from the interface
    gfx.draw_clr = out_p->GetCrntDrawColor();
    gfx.fill_clr = out_p->GetCrntFillColor();
    gfx.border_width = out_p->GetCrntPenWidth();

    out_p->ClearStatusBar();

    id = manager_p->GenerateNextId();
}

//Execute the action
void AddTrnglAction::Execute()
{
    trngl = new CTrngl(p1, p2, p3, gfx);
    trngl->SetId(id);
    manager_p->AddFigure(trngl);
}

void AddTrnglAction::Undo()
{
    manager_p->DeleteFigure(id);
}