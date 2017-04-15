#include "Rotate.h"

Rotate::Rotate(ApplicationManager * app_p) :Action(app_p)
{
}

void Rotate::ReadActionParameters()
{
	Output *out_p = manager_p->GetOutput();
	Input *in_p = manager_p->GetInput();
	out_p->PrintMessage("Enter One Of These Angles To Rotate [90 || 180 || 270] ");
	deg = stoi(in_p->GetString(out_p));
	out_p->ClearStatusBar();
	out_p->ClearTToolBar();
}

void Rotate::Execute()
{
	manager_p->RotateSelected(deg);
}

void Rotate::Undo()
{
	manager_p->RotateSelected(360 - deg);
}
