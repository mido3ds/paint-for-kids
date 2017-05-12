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
    in_p->GetClick(x, y);
    lastC = C;
    C = in_p->GetColor(x, y);
    out_p->ClearDrawArea();
    out_p->ClearStatusBar();
	out_p->ClearTempToolbar();
}

void ChFillColorAction::Execute()
{
    if (!manager_p->SetSelectedFillColor(C)) {
        Output* out_p = manager_p->GetOutput();
        out_p->SetFillColor(C);
		UI.IsFilled = true;
    }
}

void ChFillColorAction::Undo()
{
    if (!manager_p->SetSelectedFillColor(lastC)) {
        Output* out_p = manager_p->GetOutput();
        out_p->SetFillColor(lastC);
    }
}