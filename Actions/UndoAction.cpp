#include "UndoAction.h"

UndoAction::UndoAction(ApplicationManager* app_p)
    : Action(app_p, false)
{}

void UndoAction::ReadActionParameters()
{
}

void UndoAction::Execute(bool redo)
{
    manager_p->Undo();
}

void UndoAction::Undo()
{
}