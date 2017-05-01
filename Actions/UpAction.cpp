#include "UpAction.h"

UpAction::UpAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void UpAction::ReadActionParameters()
{
}

void UpAction::Execute()
{
    Output* out_p = manager_p->GetOutput();

    manager_p->SendSelectedUp();
}

void UpAction::Undo()
{
    manager_p->SendSelecteDown();
}