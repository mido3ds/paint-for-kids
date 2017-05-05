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
	out_p->CreateBorderWidth();
	do {
		out_p->PrintMessage("Choose The Prefered Border Width");
		in_p->GetClickPoint(x, y);
	} while (x < UI.TToolBarX || x > 4 * UI.MenuItemWidth || y < UI.TToolBarY || y > UI.TToolBarY + UI.TToolBarHeight);
	int ClickedItemOrder = (x / UI.MenuItemWidth);
	switch (ClickedItemOrder)
	{
	case 0:
		w = 1;
		break;
	case 1:
		w = 3;
		break;
	case 2:
		w = 6;
		break;
	case 3:
		w = 10;
		break;
	default:
		w = 3;
		break;
	}
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