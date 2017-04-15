#include "UpAction.h"

Up::Up(ApplicationManager * app_p) :Action(app_p)
{
}

void Up::ReadActionParameters()
{
}

void Up::Execute()
{
	Output *out_p = manager_p->GetOutput();
	out_p->ClearTToolBar();
	manager_p->BringSelectedUp();
}

void Up::Undo()
{
	manager_p->SendSelecteDown();
}
