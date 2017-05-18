#include "RedoAction.h"

RedoAction::RedoAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void RedoAction::ReadActionParameters()
{
}

void RedoAction::Execute(bool redo)
{
    manager_p->Redo();
}

void RedoAction::Undo()
{
}