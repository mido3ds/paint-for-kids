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
	int numOfFigs = manager_p->GetNumFigures();
	vector <color> colors = manager_p->GetColors();		// Get The List Of Avialable Colors
	do {

		in_p->GetPointClicked(x, y);
		fig = manager_p->GetFigure(x, y);

		numOfFigs--;									// Should Be Reduced After Correct Pick

	} while (numOfFigs > 0);
}

void PickByColor::Execute()
{
}

void PickByColor::Undo()
{
}
