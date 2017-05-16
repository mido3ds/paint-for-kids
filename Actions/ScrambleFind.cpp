#include "ScrambleFind.h"

ScrambleFind::ScrambleFind(ApplicationManager* app_p)
    : Action(app_p, false),

	left_figs(manager_p->GetCopyOfFigures()),
	right_figs(manager_p->GetCopyOfFigures()),

    out_p(manager_p->GetOutput()),
	in_p(manager_p->GetInput())
{
	middle_line.SetPoints({ UI.width / 2 - 3, 50 }, { UI.width / 2 + 3, UI.StatusBarY });
	middle_line.SetBorderWidth(3);
}

ScrambleFind::~ScrambleFind()
{
    // delete all copied figures
	for (auto& fig : right_figs)
		delete fig;

	for (auto& fig : left_figs)
        delete fig;
}

void ScrambleFind::ReadActionParameters() // prepare game 
{
    // resize the graph to half its size, put at left side 
	out_p->ClearDrawArea();
	out_p->ClearStatusBar();
    
    for (auto& fig : left_figs)
    {
		fig->Resize(0.5);
        fig->MoveToLeftSide();
    }
	
    for (auto& fig : right_figs)
    {
        fig->Resize(0.5);
		fig->RandomizePosition();
    }

    // some action :D
    out_p->PrintMessage(
        "Welcome in Scramble & Find, Game of the Century!"
        "					   "
        "Please wait, Loading ..."
    );

	Sleep(SECOND);
}

void ScrambleFind::Execute() // game mainloop
{
	ActionType act = ActionType::EMPTY;
	int invalid_count = 0, valid_count = 0;
    bool finish = false, valid_choice = false;
    CFigure *fig1 = nullptr, *fig2 = nullptr;
    Point clicked_point;

    // gameloop
    while (right_figs.size() > 0 && !finish) 
    {
        fig1 = ChooseRandomFigure();
	    fig1->SetDrawColor(UI.HighlightColor);

        // draw
        UpdateInterface();

        while (!valid_choice) 
        {
			UpdateMessage(invalid_count, valid_count);

            // get action
            act = in_p->GetUserAction();
            clicked_point = in_p->GetLastClickedPoint();
			if (act == EXIT || act == TO_DRAW || act == SCRAMBLE)
			{
				finish = true;
				break;
			}

            // get clicked figure
            fig2 = ApplicationManager::GetFigure(right_figs, clicked_point);

            // check two figures matching by id
            if (fig2 != nullptr)
            {
                if (fig1->GetId() == fig2->GetId()) // valid
                {
                    valid_choice = true;
                    valid_count++;

                    // erase them from figs
					left_figs.erase(find(left_figs.begin(), left_figs.end(), fig1));  // erase fig1
					right_figs.erase(find(right_figs.begin(), right_figs.end(), fig2)); // erase fig2

                    delete fig1;
                    delete fig2;
                }
				else
                    invalid_count++;
            }
        }

        valid_choice = false;
    }

    // final message
    UpdateMessage(invalid_count, valid_count, true);

	if (act == TO_DRAW || act == EXIT)
		manager_p->ExecuteAction(act);
}

void ScrambleFind::Undo()
{
}

void ScrambleFind::UpdateInterface()
{
    out_p->ClearDrawArea();
    out_p->ClearStatusBar();

    middle_line.Draw(out_p);

    // draw left figures
    for (auto& fig : right_figs)
        fig->Draw(out_p);
    
    // draw right figures
    for (auto& fig : left_figs)
        fig->Draw(out_p);
}

CFigure* ScrambleFind::ChooseRandomFigure()
{
    if (left_figs.size() != 0)
        return left_figs[rand() % left_figs.size()];
    else 
        return nullptr;
}

void ScrambleFind::UpdateMessage(int invalid, int valid, bool is_final)
{
	int final_grade;

    if (is_final)
    {
        // diplay a final grade 
		if ((valid + invalid) != 0)
			final_grade = (valid) / static_cast<double>(invalid + valid) * 100;
		else
			final_grade = 0;

        out_p->PrintMessage("Final grade = " + to_string(final_grade) + "%");
		out_p->ClearDrawArea();

		Sleep(2 * SECOND);
    }
    else
    {
        out_p->ClearStatusBar();
        out_p->PrintMessage(
            "Valid trials: " + to_string(valid) + " Invalid trials: " 
            + to_string(invalid) 
            + "                   Click on highlighted figure"
        );
    }
}