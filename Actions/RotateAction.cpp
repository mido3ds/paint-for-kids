#include "RotateAction.h"

RotateAction::RotateAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void RotateAction::ReadActionParameters()
{
}

void RotateAction::Execute()
{
    manager_p->RotateSelected(deg);
}

void RotateAction::Undo()
{
    manager_p->RotateSelected(360 - deg);
}