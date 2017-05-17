#include "PickByTypeAndColor.h"


PickByTypeAndColor::PickByTypeAndColor(ApplicationManager * app_p) 
	: Action(app_p, false)
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

		fig = manager_p->GetFigure(figures, p);
		if (fig)
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
			type = typeid(fig).hash_code();
			correct++;
			PrintPickInfo(fig,c,correct,wrong);
			DeleteCorrect(fig->GetId());		// Deleting The Correct Figure Clicked
			numOfSameTypeAndColor = GetNumFigsSameTypeAndColor(c, isfilled, type);					// Reducing The Number Of Same Color Figs If Correct
			numOfFigs--;												// Reducing the Total Number Of Figure Because Of Deleted Figure
			manager_p->UpdateInterface(figures);
		}
		else
		{
			out_p->PrintMessage("No Figure In This Area, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), RED);
			continue;
		}
		while (numOfSameTypeAndColor > 0)
		{
			in_p->GetClick(p.x, p.y);
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
				PrintPickInfo(fig, c, correct, wrong);
				if (Correct(fig))
				{
					DeleteCorrect(fig->GetId());		// Deleting The Correct Figure Clicked
					numOfSameTypeAndColor--;
					numOfFigs--;
					manager_p->UpdateInterface(figures);			// Re Draw The Interface With The New Figure List
					correct++;
					out_p->PrintMessage("Correct, Very Good, Keep Going            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), GREEN);
					Sleep(1000);
				}
				else
				{
					wrong++;
					out_p->PrintMessage("Wrong Answer, Try Agian            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), RED);
					Sleep(1000);
				}
			}
			else
			{
				out_p->PrintMessage("No Figure In This Area, Try Agian            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), RED);
				continue;
			}
		}
	}

	if (correct == 0 && wrong == 0) {
		out_p->PrintMessage("No Figures To Play Please Back And Draw Some Figures Or Load Old Paint", YELLOW, true);
	}
	else {
		out_p->PrintMessage("Your Grade Is: " + std::to_string(((correct*100) / (correct + wrong))), ORANGE);
		Sleep(1000);
	}
}

void PickByTypeAndColor::Undo()
{
}

PickByTypeAndColor::~PickByTypeAndColor()
{
	for (auto& fig : figures)
        delete fig;
}

int PickByTypeAndColor::GetNumFigsSameTypeAndColor(color C, bool isfilled,int type)
{
	int num = 0;
	for (auto &figure : figures) {
		if (typeid(figure).hash_code() == type) {
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
		
	}
	return num;
}

void PickByTypeAndColor::DeleteCorrect(int id)
{
	for (auto itr = figures.begin(); itr != figures.end(); itr++) 
		if ((*itr)->GetId() == id)
		{
			delete *itr;
			figures.erase(itr);
			return;
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
	if (dynamic_cast<CLine *> (fig)) {
		if (fig->GetDrawColor() == c) {
			return true;
		}
	}
	else if (fig->IsFilled() == isfilled && typeid(fig).hash_code() == type)
		if (fig->GetFillColor() == c)
			return true;

	return false;
}

void PickByTypeAndColor::PrintPickInfo(CFigure * fig, color c, int correct, int wrong)
{
	Output* out_p = manager_p->GetOutput();
	if (dynamic_cast<CCircle *> (fig)) {
		if (isfilled)
		{
			out_p->PrintMessage("Pick All Circles Of This Color            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), GREEN);
			DrawColorCircle(c);
		}
		else
		{
			out_p->PrintMessage("Pick All None Filled Circles            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), GREEN);
		}
	}
	else if (dynamic_cast<CTrngl *> (fig)) {
		if (isfilled)
		{
			out_p->PrintMessage("Pick All Triangles Of This Color            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), GREEN);
			DrawColorCircle(c);
		}
		else
		{
			out_p->PrintMessage("Pick All None Filled Triangles            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), GREEN);
		}
	}
	else if (dynamic_cast<CLine *> (fig)) {
		if (isfilled)
		{
			out_p->PrintMessage("Pick All Lines Of This Color            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), GREEN);
			DrawColorCircle(c);
		}
		else
		{
			out_p->PrintMessage("Pick All Lines           Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), GREEN);
		}
	}
	else if (dynamic_cast<CRectangle *> (fig)) {
		if (isfilled)
		{
			out_p->PrintMessage("Pick All Rectangles Of This Color            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), GREEN);
			DrawColorCircle(c);
		}
		else
		{
			out_p->PrintMessage("Pick All None Filled Rectangles            Correct Answers: " + to_string(correct) + "      Wrong Answers: " + to_string(wrong), GREEN);
		}
	}
}
