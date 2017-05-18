#include "SendUpAction.h"

SendUpAction::SendUpAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void SendUpAction::ReadActionParameters()
{
	IDs = manager_p->GetSelectedIDs();
}

void SendUpAction::Execute(bool redo)
{
	if (!redo)
		manager_p->SendSelectedUp();
	else
		manager_p->SendUndoUp(IDs);
}

void SendUpAction::Undo()
{
    manager_p->SendUndoDown(IDs);
}