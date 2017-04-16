#include "DownAction.h"

DownAction::DownAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void DownAction::ReadActionParameters()
{
}

void DownAction::Execute()
{
    Output* out_p = manager_p->GetOutput();
    out_p->ClearTToolBar();
    manager_p->SendSelecteDown();
}

void DownAction::Undo()
{
    manager_p->SendSelectedUp();
}
