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
    last_fill_clr = fill_clr;
    fill_clr = in_p->GetColor(x, y);

    out_p->ClearDrawArea();
    out_p->ClearStatusBar();
	out_p->ClearTempToolbar();
}

void ChFillColorAction::Execute()
{
    Output* out_p = manager_p->GetOutput();

    if (!manager_p->SetSelectedFillColor(fill_clr)) 
    {
        out_p->SetFillColor(fill_clr);
		UI.IsFilled = true;
    }
}

void ChFillColorAction::Undo()
{
    if (!manager_p->SetSelectedFillColor(last_fill_clr)) 
        manager_p->GetOutput()->SetFillColor(last_fill_clr);
}