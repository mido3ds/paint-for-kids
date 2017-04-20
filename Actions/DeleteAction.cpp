#include "DeleteAction.h"

DeleteAction::DeleteAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void DeleteAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    if (manager_p->Num_Selected == 0)
        out_p->PrintMessage("No Selected Figures To Move");
}

void DeleteAction::Execute()
{
    if (manager_p->Num_Selected > 0) {
        clipboard = manager_p->DeleteActionSelected();
        deleteActiond = true;
    }
}

void DeleteAction::Undo()
{
    if (deleteActiond) {
        for (int i = 0; i < clipboard.size(); i++) {
            manager_p->AddFigure(clipboard[i]);
        }
        deleteActiond = false;
    }
}