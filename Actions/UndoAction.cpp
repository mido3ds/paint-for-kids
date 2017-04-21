#include "UndoAction.h"

UndoAction::UndoAction(ApplicationManager* app_p)
    : Action(app_p), can_undo(false)
{
}

void UndoAction::ReadActionParameters()
{
}

void UndoAction::Execute()
{
    manager_p->Undo();
    manager_p->GetOutput()->ClearDrawArea();
}

void UndoAction::Undo()
{
}