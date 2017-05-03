#include "ScrambleFind.h"

ScrambleFind::ScrambleFind(ApplicationManager* app_p)
    : Action(app_p, false)

	,left_figs(manager_p->GetCopyOfFigures())
	,right_figs(manager_p->GetCopyOfFigures())

    ,middle_line({ UI.width / 2 - 3, 50 }, { UI.width / 2 + 3, UI.StatusBarY }, info)

    ,out_p(manager_p->GetOutput())
	,in_p(manager_p->GetInput())
{
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
    for (auto& fig : right_figs)
    {
        fig->MoveToLeftSide();
        fig->Resize(0.5);
    }
	
	ShuffleFigures();
}

void ScrambleFind::Execute() // game mainloop
{
	ActionType act = ActionType::EMPTY;
	int invalid_count = 0, valid_count = 0;
    CFigure *fig1 = nullptr, *fig2 = nullptr;
    Point clicked_point;

	while (right_figs.size() > 0) 
	{
        // redraw them
        UpdateInterface();

        // show counters for valid and invalid user trials
        out_p->PrintMessage("Valid trials: " + to_string(valid_count) + " Invalid trials: " + to_string(invalid_count));

        // get random figure from left
        fig1 = RandomFigure();
        fig1->SetDrawClr(UI.HighlightColor);

        out_p->PrintMessage("Click on highlighted figure");

        // TODO: count the invalid and valid 
        while (fig2 == nullptr) 
        {
            act = in_p->GetUserAction();
            clicked_point = in_p->GetClickedPoint();

            if (act == EXIT || act == SCRAMBLE || act == TO_DRAW)
                goto finish;

            // get fig2 at that point
            fig2 = GetFigure(clicked_point);

            // check two figures matching by id
            if (fig2 != nullptr && fig1->GetId() == fig2->GetId())
            {
                // erase them from figs
                right_figs.erase(right_figs.find(fig1));
                left_figs.erase(left_figs.find(fig1));

                delete fig1;
                delete fig2;

                fig1 = fig2 = nullptr;
            }
        }

    }

    // diplay a final grade 
    finish:
        out_p->PrintMessage("final grade is " + to_string(valid_count)); // TODO: what is final grade?
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
        fig->Draw();
    
    // draw right figures
    for (auto& fig : left_figs)
        fig->Draw();
}

CFigure* ScrambleFind::GetFigure(Point p)
{
    ApplicationManager::GetFigure(left_figs, clicked_point)
}