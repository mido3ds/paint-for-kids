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

    out_p->PrintMessage("Please Enter the Border Width If You Don't Want To Change It Type 3");
    last_pen_width = pen_width;
	out_p->CreateBorderToolbar();

	do 
	{
		out_p->PrintMessage("Choose The Prefered Border Width");
		in_p->GetClick(x, y);
	} 
	while (x < UI.TToolBarX || x > 4 * UI.MenuItemWidth || y < UI.TToolBarY || y > UI.TToolBarY + UI.TToolBarHeight);

	int ClickedItemOrder = (x / UI.MenuItemWidth);
	switch (ClickedItemOrder)
	{
		case 0: pen_width = 1; break;
		case 1: pen_width = 3; break;
		case 2: pen_width = 10; break;
		case 3: pen_width = 15; break;
		default: pen_width = 3; break;
	}
	UI.LastPenWidth = pen_width;

    out_p->PrintMessage("Please Choose Your Favorite Color To Change Border Color");
    out_p->CreateColorBar();
    in_p->GetClick(x, y);
    last_draw_clr = draw_clr;
    draw_clr = in_p->GetColor(x, y);

	UI.LastDrawColor = draw_clr;

    out_p->ClearStatusBar();
    out_p->ClearDrawArea();
	out_p->ClearTempToolbar();
}

void ChBorderAction::Execute(bool redo)
{
    Output* out_p = manager_p->GetOutput();

	if (!redo)
		IDs = manager_p->SetSelectedBorder(pen_width, draw_clr);
	else {
		manager_p->SetUndoBorder(pen_width, draw_clr, IDs);
	}

	if (IDs.empty())
	{
        out_p->SetPenWidth(pen_width);
        out_p->SetDrawColor(draw_clr);
    }
}

void ChBorderAction::Undo()
{
    Output* out_p = manager_p->GetOutput();

	if (IDs.empty())
	{
		out_p->SetPenWidth(last_pen_width);
		out_p->SetDrawColor(last_draw_clr);
	}
	else
		manager_p->SetUndoBorder(last_pen_width, last_draw_clr, IDs);
}