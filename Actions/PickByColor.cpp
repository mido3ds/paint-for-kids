#include "PickByColor.h"

PickByColor::PickByColor(ApplicationManager * app_p) :Action(app_p)
{
}

void PickByColor::ReadActionParameters()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	out_p->PrintMessage("Picking With Color");
	figures = manager_p->GetCopyOfFigures();				// Coping All Figues
	//manager_p->UpdateInterface(figures);			// Re Draw The Interface With The New Figure List
}

void PickByColor::Execute()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	CFigure *fig;
	Point p;
	manager_p->UpdateInterface(figures);
	int numOfSameColor = 0;
	int numOfFigs = manager_p->GetNumFigures();		// Number Of All Figures
	while (numOfFigs > 0) {
		out_p->CreateRestartGame();				// Restart And Exit Game Bar
		in_p->GetClickPoint(p.x, p.y);		// Getting The First Piont To Git The First Figure
		if (p.y > 0 && p.y < UI.ToolBarHeight)
		{
			int IconClicked = p.x / UI.MenuItemWidth;
			switch (IconClicked)
			{
			case 0:
				figures = manager_p->GetCopyOfFigures();
				PickByColor::Execute();
				break;
			case 1:
				out_p->CreatePlayToolBar();
				return;
			default:
				break;
			}
		}
		fig = ApplicationManager::GetFigure(figures, p);	// Getting The First Figure
		if (fig)		// If The Piont Is In Figure
		{
			c = fig->GetFillColor();
			isfilled = fig->IsFilled();
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

			in_p->GetClickPoint(p.x, p.y);
			if (p.y > 0 && p.y < UI.ToolBarHeight)
			{
				int IconClicked = p.x / UI.MenuItemWidth;
				switch (IconClicked)
				{
				case 0:
					figures = manager_p->GetCopyOfFigures();
					PickByColor::Execute();
					break;
				case 1:
					out_p->CreatePlayToolBar();
					return;
				default:
					break;
				}
			}
			fig = ApplicationManager::GetFigure(figures, p);	// Getting The First Figure
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
			if (figure->GetFillColor().ucBlue == C.ucBlue && figure->GetFillColor().ucGreen == C.ucGreen && figure->GetFillColor().ucRed == C.ucRed) // This Is Rediculous But I Have No Chiose
				num++;
		}
		else if (figure->IsFilled() == isfilled)
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
	int raduis = 15;
	GfxInfo info;
	info.is_filled = true;
	info.border_width = 1;
	info.draw_clr = c;
	info.fill_clr = c;
	out_p->DrawCircle(p1, raduis, info, false);
}

bool PickByColor::correct(CFigure * fig)
{
	if (fig->IsFilled() == isfilled)
	{
		if (fig->GetFillColor().ucBlue == c.ucBlue && fig->GetFillColor().ucGreen == c.ucGreen && fig->GetFillColor().ucRed == c.ucRed)
		{
			return true;
		}
	}
	return false;
}
