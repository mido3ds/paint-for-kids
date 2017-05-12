#include "PickByType.h"

PickByType::PickByType(ApplicationManager * app_p) :Action(app_p)
{
}

void PickByType::ReadActionParameters()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	out_p->PrintMessage("Picking With Color");
	figures = manager_p->GetCopyOfFigures();				// Coping All Figues
}

void PickByType::Execute()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	CFigure *fig;
	Point p;
	float correct = 0;
	float wrong = 0;
	string type;
	manager_p->UpdateInterface(figures);
	int numOfSameType = 0;
	int numOfFigs = manager_p->GetNumFigures();		// Number Of All Figures
	while (numOfFigs > 0) {
		
		out_p->CreateRestartGame();
		out_p->PrintMessage("Choose Your First Figure");
		in_p->GetClick(p.x, p.y);
		if (p.y > 0 && p.y < UI.ToolBarHeight)		// Chack If the User Want To Restart The Game Or Exit It
		{
			int IconClicked = p.x / UI.MenuItemWidth;
			switch (IconClicked)
			{
				case 0:						// If Restart Begien From The Executing The Action Again
					figures = manager_p->GetCopyOfFigures();
					PickByType::Execute();
					break;
				case 1:						// If Exit return To Play Mode
					out_p->CreatePlayToolBar();
					return;

				default:
					break;
			}
		}
		fig = manager_p->GetFigure(figures, p);
		
		if (fig) {

			correct++;
			if (fig->GetType() == "Circle") {
				out_p->PrintMessage("Pick All Circles            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
				type = "Circle";
			} 
			else if (fig->GetType() == "Triangle") {
				out_p->PrintMessage("Pick All Triangles            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
				type = "Triangle";
			}
			else if(fig->GetType() == "Line") {
				out_p->PrintMessage("Pick All Lines            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
				type = "Line";
			}
			else if(fig->GetType() == "Rectangle") {
				out_p->PrintMessage("Pick All Rectangles            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
				type = "Rectangle";
			}
			DeleteCorrect(fig->GetId());		// Deleting The Correct Figure Clicked
			numOfSameType = GetNumFigsSameType(type);					// Reducing The Number Of Same Type Figs If Correct
			numOfFigs--;												// Reducing the Total Number Of Figure Because Of Deleted Figure
			manager_p->UpdateInterface(figures);			// Re Draw The Interface With The New Figure List
		}
		else {
			out_p->PrintMessage("No Figure In This Area, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
			continue;
		}

		while (numOfSameType > 0) {

			in_p->GetClick(p.x, p.y);
			if (p.y > 0 && p.y < UI.ToolBarHeight)
			{
				int IconClicked = p.x / UI.MenuItemWidth;
				switch (IconClicked)
				{
					case 0:
						figures = manager_p->GetCopyOfFigures();
						PickByType::Execute();
						break;
					case 1:
						out_p->CreatePlayToolBar();
						return;

					default:
						break;
				}
			}
			fig = ApplicationManager::GetFigure(figures, p);

			if (fig) {

				if (fig->GetType() == type) {
					// Correct Figure
					correct++;
					DeleteCorrect(fig->GetId());
					numOfSameType--;
					numOfFigs--;
					manager_p->UpdateInterface(figures);
					out_p->PrintMessage("Correct, Very Good, Keep Going            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
					Sleep(400);
				}
				else {
					// Wrong Figure
					wrong++;
					out_p->PrintMessage("Wrong Answer, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
					Sleep(400);
				}

			}
			else {

				wrong++;
				out_p->PrintMessage("Wrong Answer, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong));
				Sleep(400);

			}

		}

	}
	if (correct == 0 && wrong == 0) {
		out_p->PrintMessage("No Figures To Play Please Back And Draw Some Figures Or Load Old Paint");
	}
	else {
		out_p->PrintMessage("Your Grade Is: " + std::to_string((int)((correct / (correct + wrong)) * 100)));
		Sleep(1000);
	}
}

void PickByType::Undo()
{
}

int PickByType::GetNumFigsSameType(string type)
{
	int num = 0;
	for (auto &fig : figures) {
		if (fig->GetType() == type)
			num++;
	}
	return num;
}

void PickByType::DeleteCorrect(int id)
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
