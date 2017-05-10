#include "SendUpAction.h"

SendUpAction::SendUpAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void SendUpAction::ReadActionParameters()
{
	Output *out_p = manager_p->GetOutput();
	out_p->ClearStatusBar();
}

void SendUpAction::Execute()
{
    Output* out_p = manager_p->GetOutput();

    manager_p->SendSelectedUp();
}

void SendUpAction::Undo()
{
    manager_p->SendSelecteDown();
}