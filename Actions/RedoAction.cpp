#include "RedoAction.h"

RedoAction::RedoAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void RedoAction::ReadActionParameters()
{
	Output *out_p = manager_p->GetOutput();
	out_p->ClearStatusBar();
}

void RedoAction::Execute()
{
    manager_p->Redo();
    manager_p->GetOutput()->ClearDrawArea();
}

void RedoAction::Undo()
{
}