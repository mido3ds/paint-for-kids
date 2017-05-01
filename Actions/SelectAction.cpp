#include "SelectAction.h"

SelectAction::SelectAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void SelectAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();
    out_p->PrintMessage("Please Click On The Figure You Want To Select ..");
    in_p->GetPointClicked(p.x, p.y);
    out_p->ClearStatusBar();
}

void SelectAction::Execute()
{

    selected = manager_p->GetFigure(p.x, p.y);
    while (selected == nullptr)
        ReadActionParameters();
    if (selected != nullptr && !selected->IsSelected()) {
		selected->SetSelected(true);
        originaldraw = selected->draw_clr;
        //originalfill = Selected->fill_clr;
		manager_p->SetNumSelected(manager_p->GetNumSelected() + 1);
        manager_p->PrintSelectedSize();
    }
}
void SelectAction::Undo()
{
}
