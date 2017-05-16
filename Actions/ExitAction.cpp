#include "ExitAction.h"

ExitAction::ExitAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void ExitAction::ReadActionParameters()
{
}

void ExitAction::Execute()
{
    // if not saved, ask user to save it
    if (!manager_p->IsSaved())
    {
        Output* out_p = manager_p->GetOutput();
        Input* in_p = manager_p->GetInput();


        out_p->PrintMessage("Figures are not saved, Do you want to save before exit? y/n");
        string input = in_p->GetString(out_p);

        if (input == "y" || input == "Y")
            manager_p->ExecuteAction(SAVE);
    }

	manager_p->Exit();
}

void ExitAction::Undo()
{
}