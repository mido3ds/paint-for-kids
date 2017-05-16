#include "SendDownAction.h"

SendDownAction::SendDownAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void SendDownAction::ReadActionParameters()
{
}

void SendDownAction::Execute()
{
    manager_p->SendSelecteDown();
}

void SendDownAction::Undo()
{
    manager_p->SendSelectedUp();
}