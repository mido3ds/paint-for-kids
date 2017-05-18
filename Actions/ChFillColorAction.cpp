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
	UI.LastFillColor = fill_clr;

    out_p->ClearDrawArea();
    out_p->ClearStatusBar();
	out_p->ClearTempToolbar();
}

void ChFillColorAction::Execute(bool redo)
{
    Output* out_p = manager_p->GetOutput();
	if (!redo)
		IDs = manager_p->SetSelectedFillColor(fill_clr);
	else {
		manager_p->SetUndoFillColor(fill_clr, IDs);
	}
    if (IDs.empty()) 
    {
        out_p->SetFillColor(fill_clr);
		UI.IsFilled = true;
    }
}

void ChFillColorAction::Undo()
{
	if (IDs.empty()) {
		manager_p->GetOutput()->SetFillColor(last_fill_clr);
		UI.IsFilled = is_filled;
	}
	else {
		manager_p->SetUndoFillColor(last_fill_clr, IDs);
	}
}