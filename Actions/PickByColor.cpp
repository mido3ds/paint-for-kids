#include "PickByColor.h"

PickByColor::PickByColor(ApplicationManager * app_p) :Action(app_p)
{
}

void PickByColor::ReadActionParameters()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	out_p->PrintMessage("Picking With Color");
	int x, y;
	CFigure *fig;
	do {

		in_p->GetPointClicked(x, y);
		fig = manager_p->GetFigure(x, y);


	} while (manager_p->GetNumFigures() > 0);
}

void PickByColor::Execute()
{
}

void PickByColor::Undo()
{
}
