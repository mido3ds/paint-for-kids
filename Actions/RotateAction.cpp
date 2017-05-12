#include "RotateAction.h"

RotateAction::RotateAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void RotateAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();
    out_p->PrintMessage("Enter One Of These Angles To RotateAction [90 || 180 || 270] ");
    out_p->ClearStatusBar();
}

void RotateAction::Execute()
{
    manager_p->RotateSelected(deg);
}

void RotateAction::Undo()
{
    manager_p->RotateSelected(360 - deg);
}