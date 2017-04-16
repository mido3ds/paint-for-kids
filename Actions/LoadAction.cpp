#include "LoadAction.h"

LoadAction::LoadAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void LoadAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("File name to load: ");

    string file_name = in_p->GetString(out_p);

    in_file.open(file_name, ofstream::in);

    // TODO: make exception handling system, use throw, then remove this way of handling the error (remove bool successful)
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
        manager_p->LoadAll(in_file);
        in_file.close();
    }
}

void LoadAction::Undo()
{
}
