#include "PickByArea.h"

PickByArea::PickByArea(ApplicationManager *app_p) :Action(app_p,false)
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
	CFigure* fig=nullptr;
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	int numOfFigs = manager_p->GetNumFigures();
	manager_p->UpdateInterface(figures);
	deque<double> areas; //list of figures' areas
	for (auto& fig : figures)
	{
		areas.push_back(fig->GetArea());
	}
	sort(areas.begin(), areas.end());
	while (numOfFigs > 0)
	{
		out_p->CreateRestartGame();
		out_p->PrintMessage("Pick Figures From Bigger To Smaller            Correct Answers: " +to_string(correct)+"      Wrong Answers: "+ to_string(wrong));
		in_p->GetClick(p.x, p.y);
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
		fig=manager_p->GetFigure(figures, p);
		if (fig != nullptr)
		{
			
				if (numOfFigs==1|| areas[numOfFigs - 1] == areas[numOfFigs - 2]||areas[numOfFigs - 1]- fig->GetArea() < areas[numOfFigs - 1] - areas[numOfFigs - 2])
				{
					correct++;
					DeleteCorrect(fig->GetId());
					manager_p->UpdateInterface(figures);
					out_p->PrintMessage("Correct, Very Good, Keep Going            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
					numOfFigs--;
					Sleep(1000);
				}
				else
				{
					wrong++;
					out_p->PrintMessage("Wrong Answer, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
					Sleep(1000);
				}
			
			
		}
		else
		{
			out_p->PrintMessage("No Figure In This Area, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
			continue;
		}
	}
	if (correct == 0 && wrong == 0) {
		out_p->PrintMessage("No Figures To Play Please Back And Draw Some Figures Or Load Old Paint");
	}
	else {
		out_p->PrintMessage("Your Grade Is: " + std::to_string((correct * 100) / (correct + wrong) ));
		Sleep(1000);
	}
}


void PickByArea::Undo()
{
}

PickByArea::~PickByArea()
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
