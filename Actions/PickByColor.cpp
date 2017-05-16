#include "PickByColor.h"

PickByColor::PickByColor(ApplicationManager * app_p) 
	: Action(app_p, false)
{
}

void PickByColor::ReadActionParameters()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	out_p->PrintMessage("Picking With Color");
	figures = manager_p->GetCopyOfFigures();				// Coping All Figues
}

void PickByColor::Execute()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	CFigure *fig;
	Point p;
	float correct = 0;
	float wrong = 0;
	manager_p->UpdateInterface(figures);
	int numOfSameColor = 0;
	int numOfFigs = manager_p->GetNumFigures();		// Number Of All Figures

	while (numOfFigs > 0) {
		out_p->CreateRestartGame();				// Restart And Exit Game Bar

		out_p->PrintMessage("Choose Your First Figure");

		in_p->GetClick(p.x, p.y);		// Getting The First Piont To Git The First Figure

		if (p.y > 0 && p.y < UI.ToolBarHeight)		// Chack If the User Want To Restart The Game Or Exit It
		{
			int IconClicked = p.x / UI.MenuItemWidth;
			switch (IconClicked)
			{
			case 0:						// If Restart Begien From The Executing The Action Again
				manager_p->ExecuteAction(ActionType::PICK_AREA);
			case 1:						// If Exit return To Play Mode
				return;

			default:
				break;
			}
		}
		fig = ApplicationManager::GetFigure(figures, p);	// Getting The First Figure
		if (fig)		// If The Piont Is In Figure
		{
			if (dynamic_cast<CLine *> (fig)) {
				// If The Figure Is A Line Then Its Color Is Its Draw Color Not Fill Color
				c = fig->GetDrawColor();
				isfilled = true;
			}
			else {
				// If The Figure Is Something Else Then We Take Its Fill color
				c = fig->GetFillColor();
				isfilled = fig->IsFilled();
			}
			correct++;
			if (isfilled)
			{
				
				// If Is Filled Then Draw The Color In Status Bar
				out_p->PrintMessage("Select All Figure Of This Color            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
				DrawColorCircle(c);
			}
			else {
				out_p->PrintMessage("Select All None Filled Figures            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
			}
			DeleteCorrect(fig->GetId());		// Deleting The Correct Figure Clicked
			numOfSameColor = GetNumFigsSameColor(c, isfilled);					// Reducing The Number Of Same Color Figs If Correct
			numOfFigs--;												// Reducing the Total Number Of Figure Because Of Deleted Figure
			manager_p->UpdateInterface(figures);			// Re Draw The Interface With The New Figure List
		}
		else {
			out_p->PrintMessage("No Figure In This Area, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), RED);
			continue;
		}

		while (numOfSameColor > 0)
		{

			in_p->GetClick(p.x, p.y);
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
					out_p->PrintMessage("Select All Figure Of This Color            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
					DrawColorCircle(c);
				}
				else {
					out_p->PrintMessage("Select All None Filled Figures            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
				}
				if (PickByColor::correct(fig))
				{
					DeleteCorrect(fig->GetId());		// Deleting The Correct Figure Clicked
					numOfSameColor--;
					numOfFigs--;
					manager_p->UpdateInterface(figures);			// Re Draw The Interface With The New Figure List
					correct++;
					out_p->PrintMessage("Correct, Very Good, Keep Going            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
					Sleep(400);
				}
				else {
					wrong++;
					out_p->PrintMessage("Wrong Answer, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), RED);
					Sleep(400);
				}
			}
			else {
				wrong++;
				out_p->PrintMessage("Wrong Answer, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), RED);
				Sleep(400);
			}
		}

	}
	if (correct == 0 && wrong == 0) {
		out_p->PrintMessage("No Figures To Play Please Back And Draw Some Figures Or Load Old Paint", YELLOW);
	}
	else {
		out_p->PrintMessage("Your Grade Is: " + std::to_string((int)((correct / (correct + wrong)) * 100)), ORANGE);
		Sleep(1000);
	}
}

void PickByColor::Undo()
{
}

int PickByColor::GetNumFigsSameColor(color C , bool isfilled)
{
	int num = 0;
	for (auto &figure : figures) {
		if (dynamic_cast<CLine *> (figure)) {
			if (figure->GetDrawColor() == C) {
				num++;
			}
		}
		else if (isfilled)
		{
			if (figure->GetFillColor() == C)
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
	Point p1;
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
	if (dynamic_cast<CLine *> (fig)) {
		if (fig->GetDrawColor() == c) {
			return true;
		}
	}
	else if (fig->IsFilled() == isfilled)
	{
		if (fig->GetFillColor() == c)
		{
			return true;
		}
	}
	return false;
}


PickByColor::~PickByColor()
{
	for (auto& fig : figures)
        delete fig;
}