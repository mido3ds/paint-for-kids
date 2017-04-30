#include "LoadAction.h"

LoadAction::LoadAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void LoadAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

	// check to save if figures > 0
	if (manager_p->GetNumFigures() > 0)
	{
		out_p->PrintMessage("Do you need to save this graph before loading new? y/n");
		string input = in_p->GetString(out_p);
		if (input == "y" || input == "Y")
			manager_p->ExecuteAction(SAVE);
	}

    out_p->PrintMessage("File name to load: ");

    string file_name = in_p->GetString(out_p);

    in_file.open(file_name, ofstream::in);

    if (!in_file.is_open()) {
        out_p->PrintMessage("Cant open file!");
    } else {
        successfull = true;
    }

    out_p->ClearStatusBar();
}

void LoadAction::Execute()
{
    if (successfull) {
		manager_p->DeleteAllFigures();
        manager_p->LoadAll(in_file);
        in_file.close();
    }
}

void LoadAction::Undo()
{
}
