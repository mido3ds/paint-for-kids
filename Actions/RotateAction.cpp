#include "RotateAction.h"

RotateAction::RotateAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void RotateAction::ReadActionParameters()
{
	IDs = manager_p->GetSelectedIDs();
}

void RotateAction::Execute(bool redo)
{
	if (!redo)
		manager_p->RotateSelected(deg);
	else
		manager_p->RotateUndo(deg, IDs);
}

void RotateAction::Undo()
{
    manager_p->RotateUndo(360 - deg, IDs);
}