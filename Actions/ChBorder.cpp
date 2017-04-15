#include "ChBorder.h"

ChBorder::ChBorder(ApplicationManager * app_p) :Action(app_p)
{
}

void ChBorder::ReadActionParameters()
{
	Output *out_p = manager_p->GetOutput();
	Input *in_p = manager_p->GetInput();
	int x, y;
	w = out_p->GetCrntPenWidth();
	out_p->PrintMessage("Please Enter the Border Width If You Don't Want To Change It Type 3");
	lastW = w;
	w = stoi(in_p->GetString(out_p));
	out_p->PrintMessage("Please Choose Your Favorite Color To Change Border Color");
	out_p->CreateColorBar();
	in_p->GetPointClicked(x ,y);
	lastC = C;
	C = in_p->PickColor(x, y);
	out_p->ClearStatusBar();
	out_p->ClearDrawArea();
}

void ChBorder::Execute()
{
	if (!manager_p->ChangeSelectedBorder(w, C))
	{
		Output *out_p = manager_p->GetOutput();
		out_p->SetCrntPenWidth(w);
		out_p->SetCrntDrawColor(C);
	}
}

void ChBorder::Undo()
{
	if (!manager_p->ChangeSelectedBorder(lastW, lastC))
	{
		Output *out_p = manager_p->GetOutput();
		out_p->SetCrntPenWidth(lastW);
		out_p->SetCrntDrawColor(lastC);
	}
}
