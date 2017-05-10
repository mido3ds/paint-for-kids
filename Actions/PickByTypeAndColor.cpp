#include "PickByTypeAndColor.h"


PickByTypeAndColor::PickByTypeAndColor(ApplicationManager * app_p) :Action(app_p,false)
{
}

void PickByTypeAndColor::ReadActionParameters()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	out_p->PrintMessage("Picking Colored Figures...");
	Sleep(1000);
	figures = manager_p->GetCopyOfFigures();
}

void PickByTypeAndColor::Execute()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	CFigure *fig;
	Point p;
	
	manager_p->UpdateInterface(figures);
	int numOfSameTypeAndColor = 0;
	int numOfFigs = manager_p->GetNumFigures();
	while (numOfFigs > 0)
	{
		out_p->CreateRestartGame();				// Restart And Exit Game Bar

		out_p->PrintMessage("Choose Your First Figure");

		in_p->GetClickPoint(p.x, p.y);		// Getting The First Piont To Git The First Figure

		if (p.y > 0 && p.y < UI.ToolBarHeight)		// Chack If the User Want To Restart The Game Or Exit It
		{
			int IconClicked = p.x / UI.MenuItemWidth;
			switch (IconClicked)
			{
			case 0:						// If Restart Begien From The Executing The Action Again
				ReadActionParameters();
				Execute();
				break;
			case 1:						// If Exit return To Play Mode
				out_p->CreatePlayToolBar();
				return;
			default:
				break;
			}
		}

		fig = manager_p->GetFigure(figures, p);
		if (fig)
		{
			c = fig->GetFillColor();
			type = fig->GetType();
			isfilled = fig->IsFilled();
			correct++;
			PrintPickInfo(type,c,correct,wrong);
			DeleteCorrect(fig->GetId());		// Deleting The Correct Figure Clicked
			numOfSameTypeAndColor = GetNumFigsSameTypeAndColor(c, isfilled, type);					// Reducing The Number Of Same Color Figs If Correct
			numOfFigs--;												// Reducing the Total Number Of Figure Because Of Deleted Figure
			manager_p->UpdateInterface(figures);
		}
		else
		{
			out_p->PrintMessage("No Figure In This Area, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
			continue;
		}
		while (numOfSameTypeAndColor > 0)
		{
			in_p->GetClickPoint(p.x, p.y);
			if (p.y > 0 && p.y < UI.ToolBarHeight)
			{
				int IconClicked = p.x / UI.MenuItemWidth;
				switch (IconClicked)
				{
				case 0:
					ReadActionParameters();
					Execute();
					break;
				case 1:
					out_p->CreatePlayToolBar();
					return;
				default:
					break;
				}
			}
			fig = manager_p->GetFigure(figures, p);
			if (fig)
			{
				PrintPickInfo(type, c, correct, wrong);
				if (Correct(fig))
				{
					DeleteCorrect(fig->GetId());		// Deleting The Correct Figure Clicked
					numOfSameTypeAndColor--;
					numOfFigs--;
					manager_p->UpdateInterface(figures);			// Re Draw The Interface With The New Figure List
					correct++;
					out_p->PrintMessage("Correct, Very Good, Keep Going            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
					Sleep(1000);
				}
				else
				{
					wrong++;
					out_p->PrintMessage("Wrong Answer, Try Agian            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
					Sleep(1000);
				}
			}
			else
			{
				out_p->PrintMessage("No Figure In This Area, Try Agian            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
				continue;
			}
		}
	}

	if (correct == 0 && wrong == 0) {
		out_p->PrintMessage("No Figures To Play Please Back And Draw Some Figures Or Load Old Paint");
	}
	else {
		out_p->PrintMessage("Your Grade Is: " + std::to_string(((correct*100) / (correct + wrong))));
		Sleep(1000);
	}
}

void PickByTypeAndColor::Undo()
{
}

PickByTypeAndColor::~PickByTypeAndColor()
{
}

int PickByTypeAndColor::GetNumFigsSameTypeAndColor(color C, bool isfilled,string type)
{
	int num = 0;
	for (auto &figure : figures) {
		if (isfilled && figure->GetType() == type)
		{
			if (figure->GetFillColor().ucBlue == C.ucBlue && figure->GetFillColor().ucGreen == C.ucGreen && figure->GetFillColor().ucRed == C.ucRed) // This Is Rediculous But I Have No Chiose
				num++;
		}
		else if (figure->IsFilled() == isfilled && figure->GetType() == type)
			num++;
	}
	return num;
}

void PickByTypeAndColor::DeleteCorrect(int id)
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

void PickByTypeAndColor::DrawColorCircle(color c)
{
	Point p1;
	Output *out_p = manager_p->GetOutput();
	p1.y = UI.StatusBarY + (UI.StatusBarHeight / 2) - 10;
	p1.x = 270;
	int raduis = 15;
	GfxInfo info;
	info.is_filled = true;
	info.border_width = 1;
	info.draw_clr = c;
	info.fill_clr = c;
	out_p->DrawCircle(p1, raduis, info, false);
}

bool PickByTypeAndColor::Correct(CFigure * fig)
{
	if (fig->IsFilled() == isfilled && fig->GetType() == type)
	{
		if (fig->GetFillColor().ucBlue == c.ucBlue && fig->GetFillColor().ucGreen == c.ucGreen && fig->GetFillColor().ucRed == c.ucRed)
		{
			return true;
		}
	}
	return false;
}

void PickByTypeAndColor::PrintPickInfo(string type, color c, int correct, int wrong)
{
	Output* out_p = manager_p->GetOutput();
	if (type == "Circle") {
		if (isfilled)
		{
			out_p->PrintMessage("Pick All Circles Of This Color            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
			DrawColorCircle(c);
		}
		else
		{
			out_p->PrintMessage("Pick All None Filled Circles            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
		}
	}
	else if (type == "Triangle") {
		if (isfilled)
		{
			out_p->PrintMessage("Pick All Triangles Of This Color            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
			DrawColorCircle(c);
		}
		else
		{
			out_p->PrintMessage("Pick All None Filled Triangles            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
		}
	}
	else if (type == "Line") {
		if (isfilled)
		{
			out_p->PrintMessage("Pick All Lines Of This Color            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
			DrawColorCircle(c);
		}
		else
		{
			out_p->PrintMessage("Pick All Lines           Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
		}
	}
	else if (type == "Rectangle") {
		if (isfilled)
		{
			out_p->PrintMessage("Pick All Rectangles Of This Color            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
			DrawColorCircle(c);
		}
		else
		{
			out_p->PrintMessage("Pick All None Filled Rectangles            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong));
		}
	}
}
