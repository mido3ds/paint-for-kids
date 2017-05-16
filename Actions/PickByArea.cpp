#include "PickByArea.h"

PickByArea::PickByArea(ApplicationManager *app_p) 
	: Action(app_p,false)
{
}

void PickByArea::ReadActionParameters()
{
	Output *out_p = manager_p->GetOutput();

	out_p->PrintMessage("Picking With Area ....");
	figures = manager_p->GetCopyOfFigures();

	Sleep(SECOND);
}

void PickByArea::Execute()
{
	int correct = 0;
	int wrong = 0;
	Point p;
	CFigure* fig = nullptr;
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	int num_of_figs = manager_p->GetNumFigures();

	manager_p->UpdateInterface(figures);
	deque<double> areas; //list of figures' areas

	for (auto& fig : figures)
	{
		areas.push_back(fig->GetArea());
	}

	sort(areas.begin(), areas.end());

	while (num_of_figs > 0)
	{
		out_p->CreateRestartGame();
		out_p->PrintMessage("Pick Figures From Bigger To Smaller            Correct Answers: " +to_string(correct)+"      Wrong Answers: "+ to_string(wrong), GREEN);
		in_p->GetClick(p.x, p.y);
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

		if (fig != nullptr)
		{
			
			if (num_of_figs==1|| areas[num_of_figs - 1] == areas[num_of_figs - 2]||areas[num_of_figs - 1]- fig->GetArea() < areas[num_of_figs - 1] - areas[num_of_figs - 2])
			{
				correct++;
				DeleteCorrect(fig->GetId());
				manager_p->UpdateInterface(figures);
				out_p->PrintMessage("Correct, Very Good, Keep Going            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
				num_of_figs--;
				Sleep(1000);
			}
			else
			{
				wrong++;
				out_p->PrintMessage("Wrong Answer, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), RED);
				Sleep(1000);
			}
		}
		else
		{
			out_p->PrintMessage("No Figure In This Area, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), RED);
			continue;
		}
	}

	if (correct == 0 && wrong == 0) 
		out_p->PrintMessage("No Figures To Play Please Back And Draw Some Figures Or Load Old Paint", YELLOW);
	else 
	{
		out_p->PrintMessage("Your Grade Is: " + std::to_string((correct * 100) / (correct + wrong) ), ORANGE);
		Sleep(SECOND);
	}
}

void PickByArea::Undo()
{
}

void PickByArea::DeleteCorrect(int id)
{
	for (auto itr = figures.begin(); itr != figures.end(); itr++) 
		if ((*itr)->GetId() == id)
		{
			delete *itr;
			figures.erase(itr);
			return;
		}
}

PickByArea::~PickByArea()
{
	for (auto& fig : figures)
        delete fig;
}