#include "DeleteAction.h"

DeleteAction::DeleteAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void DeleteAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    if (manager_p->GetNumSelected() == 0)
        out_p->PrintMessage("No Selected Figures To Move");
}

void DeleteAction::Execute()
{
    if (manager_p->GetNumSelected() > 0) {
        clipboard = manager_p->DeleteSelected();
        deleted = true;
    }
}

void DeleteAction::Undo()
{
    if (deleted) {
        for (int i = 0; i < clipboard.size(); i++) {
            manager_p->AddFigure(clipboard[i]);
        }
        deleted = false;
    }
}