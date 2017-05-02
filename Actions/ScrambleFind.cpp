#include "ScrambleFind.h"

ScrambleFind::ScrambleFind(ApplicationManager* app_p)
    : Action(app_p, false)
	// figs is initialized with copy of application_manager figs
	,figs(manager_p->GetCopyOfFigures()) 
{
}

ScrambleFind::~ScrambleFind()
{
	for (auto& fig : figs)
		delete fig;
}

void ScrambleFind::ReadActionParameters()
{
}

void ScrambleFind::Execute()
{
	Output* out_p = manager_p->GetOutput();
	Input* in_p = manager_p->GetInput();
	ActionType act = ActionType::EMPTY;
	int invalid_count = 0, valid_count = 0;

	// for line
	GfxInfo info;
	info.border_width = 3;
	CLine line({ UI.width / 2 - 3, 50 }, { UI.width / 2 + 3, UI.StatusBarY }, info);
	line.Draw(out_p);

    // resize the graph to half its size, put at left side 
	out_p->ClearDrawArea();
	out_p->ClearStatusBar();
    for (auto& fig : figs)
    {
        fig->MoveToLeftSide();
        fig->Resize(0.5);
    }
	
	do {
		// right_figs.randomize()

        // show counters for valid and invalid user trials 
		out_p->PrintMessage("Valid trials: " + to_string(valid_count) + " Unvalid trials: " + to_string(invalid_count));

		// fig = choose_random_figure()
		// fig.highlight()
		out_p->PrintMessage("Click on highlighted figure");

		act = in_p->GetUserAction();
		if (act == EXIT || act == SCRAMBLE || act == TO_DRAW)
			break;

		// if fig1 == fig2:
			// fig1.disappear()
			// fig2.disappear()
	} while (figs.size() > 0);

    // diplay a final grade 
	out_p->PrintMessage("final graded is " + to_string(valid_count)); // TODO: what is final grade?
}

void ScrambleFind::Undo()
{
}