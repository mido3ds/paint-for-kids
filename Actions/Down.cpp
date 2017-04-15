#include "Down.h"

Down::Down(ApplicationManager * app_p) :Action(app_p)
{
}

void Down::ReadActionParameters()
{
}

void Down::Execute()
{
	Output *out_p = manager_p->GetOutput();
	out_p->ClearTToolBar();
	manager_p->SendSelecteDown();
}

void Down::Undo()
{
	manager_p->BringSelectedUp();
}
