#include "RedoAction.h"

RedoAction::RedoAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void RedoAction::ReadActionParameters()
{
}

void RedoAction::Execute()
{
    manager_p->Redo();
}

void RedoAction::Undo()
{
}