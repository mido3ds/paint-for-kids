#include "PickByType.h"

PickByType::PickByType(ApplicationManager * app_p) 
	: Action(app_p, false)
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
	int type;
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
				manager_p->ExecuteAction(ActionType::PICK_AREA);
			case 1:						// If Exit return To Play Mode
				return;

			default:
				break;
			}
		}
		fig = manager_p->GetFigure(figures, p);
		
		if (fig) {

			correct++;
			if (dynamic_cast<CCircle *> (fig)) {
				out_p->PrintMessage("Pick All Circles            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
			} 
			else if (dynamic_cast<CTrngl *> (fig)) {
				out_p->PrintMessage("Pick All Triangles            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
			}
			else if(dynamic_cast<CLine *> (fig)) {
				out_p->PrintMessage("Pick All Lines            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
			}
			else if(dynamic_cast<CRectangle *> (fig)) {
				out_p->PrintMessage("Pick All Rectangles            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
			}

			type = typeid(fig).hash_code();

			DeleteCorrect(fig->GetId());		// Deleting The Correct Figure Clicked
			numOfSameType = GetNumFigsSameType(fig);					// Reducing The Number Of Same Type Figs If Correct
			numOfFigs--;												// Reducing the Total Number Of Figure Because Of Deleted Figure
			manager_p->UpdateInterface(figures);			// Re Draw The Interface With The New Figure List
		}
		else {
			out_p->PrintMessage("No Figure In This Area, Try Agian            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), RED);
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
						return;
					case 1:
						out_p->CreatePlayToolBar();
						return;

					default:
						break;
				}
			}
			fig = ApplicationManager::GetFigure(figures, p);

			if (fig) {

				if (typeid(fig).hash_code() == type) {
					// Correct Figure
					correct++;
					DeleteCorrect(fig->GetId());
					numOfSameType--;
					numOfFigs--;
					manager_p->UpdateInterface(figures);
					out_p->PrintMessage("Correct, Very Good, Keep Going            Correct Answers: " + std::to_string(correct) + "      Wrong Answers: " + std::to_string(wrong), GREEN);
					Sleep(400);
				}
				else {
					// Wrong Figure
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
		out_p->PrintMessage("No Figures To Play Please Back And Draw Some Figures Or Load Old Paint", YELLOW, true);
	}
	else {
		out_p->PrintMessage("Your Grade Is: " + std::to_string((int)((correct / (correct + wrong)) * 100)), ORANGE);
		Sleep(1000);
	}
}

void PickByType::Undo()
{
}

int PickByType::GetNumFigsSameType(CFigure *figure)
{
	int num = 0;
	for (auto &fig : figures) {
		if (typeid(fig) == typeid(figure))
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

PickByType::~PickByType()
{
	for (auto& fig : figures)
        delete fig;
}