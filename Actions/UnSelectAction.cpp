#include "UnSelectAction.h"

UnSelectAction::UnSelectAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void UnSelectAction::ReadActionParameters()
{
    Input* in_p = manager_p->GetInput();
    Output* out_p = manager_p->GetOutput();
    in_p->GetPointClicked(p.x, p.y);
}

void UnSelectAction::Execute()
{
    figure = manager_p->GetFigure(p.x, p.y);
    if (figure != nullptr && figure->IsSelected()) {
        figure->SetSelected(false);
        manager_p->Num_Selected--;
    }
}

void UnSelectAction::Undo()
{
    if (figure != nullptr && figure->IsSelected()) {
        figure->SetSelected(true);
        manager_p->Num_Selected++;
    }
}