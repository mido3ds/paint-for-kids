#include "MoveAction.h"

MoveAction::MoveAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void MoveAction::ReadActionParameters()
{

    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();
    if (manager_p->Num_Selected > 0) {
        out_p->PrintMessage("Please Click The Point You Want To MoveAction Selected Figure/s At");
        in_p->GetPointClicked(p.x, p.y);
        out_p->ClearStatusBar();
    } else
        out_p->PrintMessage("No Selected Figures To MoveAction");
}

void MoveAction::Execute()
{
    if (manager_p->Num_Selected > 0) {
        old = manager_p->MoveActionSelected(p);
        moveActiond = true;
    }
}

void MoveAction::Undo()
{
    if (moveActiond) {
        manager_p->ReturnMoveActiond(old);
        moveActiond = false;
    }
}