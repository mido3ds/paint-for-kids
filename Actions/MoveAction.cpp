#include "MoveAction.h"

MoveAction::MoveAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void MoveAction::ReadActionParameters()
{

    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    if (manager_p->GetNumSelected() > 0) {
        out_p->PrintMessage("Please Click The Point You Want To MoveAction Selected Figure/s At");
        in_p->GetClick(p.x, p.y);
        out_p->ClearStatusBar();
    } else
        out_p->PrintMessage("No Selected Figures To MoveAction");
}

void MoveAction::Execute()
{
    if (manager_p->GetNumSelected() > 0) {
        manager_p->MoveSelected(p, moved_figs,old);
        moved = true;
    }
}

void MoveAction::Undo()
{
    if (moved) {
		int x = old.x - p.x;
		int y = old.y - p.y;
		for (int i = 0;i < moved_figs.size();i++)
		{
			moved_figs[i]->Move(x, y);
		}
		moved_figs.clear();
        moved = false;
    }
}