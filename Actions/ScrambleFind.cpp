#include "ScrambleFind.h"

ScrambleFind::ScrambleFind(ApplicationManager* app_p)
    : Action(app_p, false)
	// l_figs is initialized with copy of application_manager figs
	,l_figs(manager_p->GetCopyOfFigures())
	,r_figs(manager_p->GetCopyOfFigures())
    ,middle_line({ UI.width / 2 - 3, 50 }, { UI.width / 2 + 3, UI.StatusBarY }, info)
    ,out_p(manager_p->GetOutput())
	,in_p(manager_p->GetInput())
{
    middle_line.SetBorderWidth(3);
}

ScrambleFind::~ScrambleFind()
{
    // delete all copied figures
	for (auto& fig : l_figs)
		delete fig;

	for (auto& fig : r_figs)
        delete fig;
}

void ScrambleFind::ReadActionParameters()
{
}

void ScrambleFind::Execute()
{
	ActionType act = ActionType::EMPTY;
	int invalid_count = 0, valid_count = 0;

    // resize the graph to half its size, put at left side 
	out_p->ClearDrawArea();
	out_p->ClearStatusBar();
    for (auto& fig : l_figs)
    {
        fig->MoveToLeftSide();
        fig->Resize(0.5);
    }
	
	ShuffleFigures();

	while (l_figs.size() > 0) 
	{
        // redraw them
        UpdateInterface();

        // show counters for valid and invalid user trials
        out_p->PrintMessage("Valid trials: " + to_string(valid_count) + " Unvalid trials: " + to_string(invalid_count));

        // get random figure from left
        auto itr = RandomFigure();
        CFigure* fig1 = *itr;
        fig1->SetDrawClr(UI.HighlightColor);

        out_p->PrintMessage("Click on highlighted figure");

        act = in_p->GetUserAction();
        if (act != DRAWING_AREA && act != EMPTY && act != STATUS)
            break;

        // get point clicked
        // get fig2 at that point
        
        // if fig1.id == fig2.id:
            // fig1.disappear()
            // fig2.disappear()
    }

    // diplay a final grade 
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
    for (auto& fig : l_figs)
        fig->Draw();
    
    // draw right figures
    for (auto& fig : r_figs)
        fig->Draw();
}