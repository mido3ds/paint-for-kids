#include "SelectAction.h"

SelectAction::SelectAction(ApplicationManager* app_p)
    : Action(app_p)
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

    Selected = manager_p->GetFigure(p.x, p.y);
    while (Selected == nullptr)
        ReadActionParameters();
    if (Selected != nullptr) {
        Selected->SetSelected(true);
        originaldraw = Selected->draw_clr;
        originalfill = Selected->fill_clr;
        manager_p->Num_Selected++;
        manager_p->PrintSelectedSize();
    }
}
void SelectAction::Undo()
{
    Selected->ChngDrawClr(originaldraw);
    Selected->ChngFillClr(originalfill);
    Selected->SetSelected(false);
    manager_p->Num_Selected--;
}
