#include "PickByColor.h"

PickByColor::PickByColor(ApplicationManager * app_p) :Action(app_p)
{
}

void PickByColor::ReadActionParameters()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	out_p->PrintMessage("Picking With Color");
	figures = manager_p->CopyFigs();				// Coping All Figues
	manager_p->UpdateInterface(figures);			// Re Draw The Interface With The New Figure List
}

void PickByColor::Execute()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	CFigure *fig;
	int x, y;
	int numOfSameColor = 0;
	int numOfFigs = manager_p->GetNumFigures();		// Number Of All Figures
	while (numOfFigs > 0) {

		in_p->GetPointClicked(x, y);		// Getting The First Piont To Git The First Figure
		fig = manager_p->GetFigure(figures, x, y);	// Getting The First Figure
		if (fig)		// If The Piont Is In Figure
		{
			c = fig->fill_clr;
			isfilled = fig->is_filled;
			if (isfilled)
			{
				// If Is Filled Then Draw The Color In Status Bar
				out_p->PrintMessage("Select All Figure Of This Color");
				DrawColorCircle(c);
			}
			else {
				out_p->PrintMessage("Select All None Filled Figures");
			}
			DeleteCorrect(fig->GetId());		// Deleting The Correct Figure Clicked
			numOfSameColor = GetNumFigsSameColor(c, isfilled);					// Reducing The Number Of Same Color Figs If Correct
			numOfFigs--;												// Reducing the Total Number Of Figure Because Of Deleted Figure
			manager_p->UpdateInterface(figures);			// Re Draw The Interface With The New Figure List
		}
		else {
			out_p->PrintMessage("No Figure In This Area, Try Agian");
			continue;
		}

		while (numOfSameColor > 0)
		{

			in_p->GetPointClicked(x, y);
			fig = manager_p->GetFigure(x, y);	// Getting The First Figure
			if (fig) {
				if (isfilled)
				{
					// If Is Filled Then Draw The Color In Status Bar
					out_p->PrintMessage("Select All Figure Of This Color");
					DrawColorCircle(c);
				}
				else {
					out_p->PrintMessage("Select All None Filled Figures");
				}
				if (correct(fig))
				{
					DeleteCorrect(fig->GetId());		// Deleting The Correct Figure Clicked
					numOfSameColor--;
					numOfFigs--;
					manager_p->UpdateInterface(figures);			// Re Draw The Interface With The New Figure List
					out_p->PrintMessage("Correct, Very Good, Keep Going");
					Sleep(400);
				}
				else {
					out_p->PrintMessage("Wrong Answer, Try Agian");
					Sleep(400);
				}
			}
			else {
				out_p->PrintMessage("Wrong Answer, Try Agian");
				Sleep(400);
			}
		}

	}
}

void PickByColor::Undo()
{
}

int PickByColor::GetNumFigsSameColor(color C , bool isfilled)
{
	int num = 0;
	for (auto &figure : figures) {
		if (isfilled)
		{
			if (figure->fill_clr.ucBlue == C.ucBlue && figure->fill_clr.ucGreen == C.ucGreen && figure->fill_clr.ucRed == C.ucRed) // This Is Rediculous But I Have No Chiose
				num++;
		}
		else
			num++;
	}
	return num;
}

void PickByColor::DeleteCorrect(int id)
{
	for (auto itr = figures.begin(); itr != figures.end(); itr++) {
		if ((*itr)->GetId() == id)
		{
			delete *itr;
			figures.erase(itr);
			return;
		}
	}
}

void PickByColor::DrawColorCircle(color c)
{
	Point p1, p2;
	Output *out_p = manager_p->GetOutput();
	p1.y = UI.StatusBarY + (UI.StatusBarHeight / 2) - 10;
	p1.x = 250;
	p2.x = p1.x;
	p2.y = p1.y - 15;
	GfxInfo info;
	info.is_filled = true;
	info.border_width = 1;
	info.draw_clr = c;
	info.fill_clr = c;
	out_p->DrawCircle(p1, p2, info, false);
}

bool PickByColor::correct(CFigure * fig)
{
	if (fig->is_filled = isfilled)
	{
		if (fig->fill_clr.ucBlue == c.ucBlue && fig->fill_clr.ucGreen == c.ucGreen && fig->fill_clr.ucRed == c.ucRed)
		{
			return true;
		}
	}
	return false;
}
