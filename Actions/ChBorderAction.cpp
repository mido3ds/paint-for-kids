#include "ChBorderAction.h"

ChBorderAction::ChBorderAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void ChBorderAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();
    int x, y;
    w = out_p->GetPenWidth();
    out_p->PrintMessage("Please Enter the Border Width If You Don't Want To Change It Type 3");
    lastW = w;
    w = stoi(in_p->GetString(out_p));
    out_p->PrintMessage("Please Choose Your Favorite Color To Change Border Color");
    out_p->CreateColorBar();
    in_p->GetClickPoint(x, y);
    lastC = C;
    C = in_p->PickColor(x, y);
    out_p->ClearStatusBar();
    out_p->ClearDrawArea();
}

void ChBorderAction::Execute()
{
    if (!manager_p->SetSelectedBorder(w, C)) {
        Output* out_p = manager_p->GetOutput();
        out_p->SetPenWidth(w);
        out_p->SetDrawColor(C);
    }
}

void ChBorderAction::Undo()
{
    if (!manager_p->SetSelectedBorder(lastW, lastC)) {
        Output* out_p = manager_p->GetOutput();
        out_p->SetPenWidth(lastW);
        out_p->SetDrawColor(lastC);
    }
}