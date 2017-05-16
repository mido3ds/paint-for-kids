#include "SendUpAction.h"

SendUpAction::SendUpAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void SendUpAction::ReadActionParameters()
{
}

void SendUpAction::Execute()
{
    manager_p->SendSelectedUp();
}

void SendUpAction::Undo()
{
    manager_p->SendSelecteDown();
}