#include "MoveAction.h"

MoveAction::MoveAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void MoveAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    if (manager_p->GetNumSelected() > 0) 
        out_p->PrintMessage("Please Click The Point You Want To Move Selected Figure/s To");
    else
        out_p->PrintMessage("No Selected Figures To Move", WHITE, true);
}

void MoveAction::Execute()
{
	Output* out_p = manager_p->GetOutput();
	Input* in_p = manager_p->GetInput();

    if (manager_p->GetNumSelected() > 0) 
	{
		in_p->GetClick(p.x, p.y);
		manager_p->MoveSelected(p, moved_figs, old);

		while ( !  in_p->IsMouseDown(LEFT_BUTTON,p.x,p.y))
		{
			p = in_p->GetMouseCoord();
			Point waste; //to pass it to the function instead of old ; to keep old point unchanged
			manager_p->MoveSelected(p, moved_figs, waste);
			manager_p->UpdateInterface(false);		// Because Of The ToolBar Framming
		}

		in_p->GetClick(p.x,p.y);
        moved = true;
    }
}

void MoveAction::Undo()
{
    if (moved) 
	{
		int x = old.x - p.x;
		int y = old.y - p.y;

		for (int i = 0;i < moved_figs.size();i++)
			moved_figs[i]->Move(x, y);
		moved_figs.clear();

        moved = false;
    }
}