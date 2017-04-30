#include "SaveAction.h"

SaveAction::SaveAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void SaveAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("File name to save at: ");

    string file_name = in_p->GetString(out_p);

    out_file.open(file_name, ofstream::out);

    if (!out_file.is_open()) {
        out_p->PrintMessage("Cant open file!");
    } else {
        successfull = true;
    }

    out_p->ClearStatusBar();
}

void SaveAction::Execute()
{
    if (successfull) {
        manager_p->SaveAll(out_file);
        out_file.close();
    }
}

void SaveAction::Undo()
{
}