#include "PasteAction.h"

PasteAction::PasteAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void PasteAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();
    out_p->PrintMessage("Please Click The Point You Want To PasteAction Selected Figure/s At");
    in_p->GetPointClicked(p.x, p.y);
    out_p->ClearStatusBar();
}

void PasteAction::Execute()
{
    clipboard = manager_p->GetClipboard();
    while (!manager_p->PasteClipboard(p))
        ReadActionParameters();
}

void PasteAction::Undo()
{
    for (auto& fig : clipboard) {
        manager_p->DeleteFigure(fig->GetId());
    }
}