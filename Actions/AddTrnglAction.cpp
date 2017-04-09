#include "AddTrnglAction.h"

AddTrnglAction::AddTrnglAction(ApplicationManager* app_p)
    : Action(app_p)
{}

void AddTrnglAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    trngl = new CTrngl();

    out_p->PrintMessage("New triangle: Click at first point");

    //Read 1st corner and store in point p1
    in_p->GetPointClicked(trngl->p1.x, trngl->p1.y);

    out_p->PrintMessage("New triangle: Click at second corner");

    //Read 2nd corner and store in point p2
    in_p->GetPointClicked(trngl->p2.x, trngl->p2.y);

    out_p->PrintMessage("New triangle: Click at third corner");

    //Read 2nd corner and store in point p2
    in_p->GetPointClicked(trngl->p3.x, trngl->p3.y);

    trngl->is_filled = false; //default is not filled
    //get drawing, filling colors and pen width from the interface
    trngl->draw_clr = out_p->GetCrntDrawColor();
    trngl->fill_clr = out_p->GetCrntFillColor();
    trngl->border_width = out_p->GetCrntPenWidth();

    out_p->ClearStatusBar();
}

//Execute the action
void AddTrnglAction::Execute()
{
    ReadActionParameters();

    manager_p->AddFigure(trngl);
}
