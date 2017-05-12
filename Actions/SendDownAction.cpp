#include "SendDownAction.h"

SendDownAction::SendDownAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void SendDownAction::ReadActionParameters()
{
	Output *out_p = manager_p->GetOutput();
	out_p->ClearStatusBar();
}

void SendDownAction::Execute()
{
    Output* out_p = manager_p->GetOutput();
    manager_p->SendSelecteDown();
}

void SendDownAction::Undo()
{
    manager_p->SendSelectedUp();
}