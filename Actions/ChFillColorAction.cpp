#include "ChFillColorAction.h"

ChFillColorAction::ChFillColorAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void ChFillColorAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();
    int x, y;
    out_p->PrintMessage("Choose Your Favourite Color");
    out_p->CreateColorBar();
    in_p->GetPointClicked(x, y);
    lastC = C;
    C = in_p->PickColor(x, y);
    out_p->ClearDrawArea();
    out_p->ClearStatusBar();
}

void ChFillColorAction::Execute()
{
    if (!manager_p->ChangeSelectedFillColor(C)) {
        Output* out_p = manager_p->GetOutput();
        out_p->SetCrntFillColor(C);
    }
}

void ChFillColorAction::Undo()
{
    if (!manager_p->ChangeSelectedFillColor(lastC)) {
        Output* out_p = manager_p->GetOutput();
        out_p->SetCrntFillColor(lastC);
    }
}