#include "SendDownAction.h"

SendDownAction::SendDownAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void SendDownAction::ReadActionParameters()
{
	IDs = manager_p->GetSelectedIDs();
}

void SendDownAction::Execute(bool redo)
{
	if (!redo)
		manager_p->SendSelecteDown();
	else {
		manager_p->SendUndoDown(IDs);
	}
}

void SendDownAction::Undo()
{
    manager_p->SendUndoUp(IDs);
}