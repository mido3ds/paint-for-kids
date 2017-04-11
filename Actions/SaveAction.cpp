#include "SaveAction.h"

SaveAction::SaveAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void SaveAction::ReadActionParameters()
{
    //TODO: test this
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("File name to save at: ");

    string file_name = in_p->GetString(out_p);

    out_file.open(file_name, ofstream::out | ofstream::app);

    // TODO: make exception handling system, use throw, then remove this way of handling the error (remove bool successful)
    if (!out_file.is_open()) {
        out_p->PrintMessage("Cant open file!");
    } else {
        successfull = true;
    }
}

void SaveAction::Execute()
{
    if (successfull) {
        manager_p->SaveAll(out_file);
        out_file.close();
    }
}
