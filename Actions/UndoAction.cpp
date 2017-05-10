#include "UndoAction.h"

UndoAction::UndoAction(ApplicationManager* app_p)
    : Action(app_p, false)
{}

void UndoAction::ReadActionParameters()
{
	Output *out_p = manager_p->GetOutput();
	out_p->ClearStatusBar();
}

void UndoAction::Execute()
{
    manager_p->Undo();
    manager_p->GetOutput()->ClearDrawArea();
}

void UndoAction::Undo()
{
}