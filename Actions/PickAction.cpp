#include "PickAction.h"

PickAction::PickAction(ApplicationManager * app_p) 
	: Action(app_p, false)
{
}

void PickAction::ReadActionParameters()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	out_p->CreatePickBar();
	out_p->PrintMessage("Pick & Hide Game .... To Start Choose A Mood To Play ");
	act = in_p->GetUserAction();
	out_p->ClearTempToolbar();
}

void PickAction::Execute()
{
	manager_p->ExecuteAction(act);
}

void PickAction::Undo()
{
}