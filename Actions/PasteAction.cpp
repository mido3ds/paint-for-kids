#include "PasteAction.h"

PasteAction::PasteAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void PasteAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("Please Click The Point You Want To Paste Selected Figure/s At");
    in_p->GetClick(p.x, p.y);
    out_p->ClearStatusBar();
}

void PasteAction::Execute()
{
	manager_p->PasteClipboard(p);
	clipboard = manager_p->GetClipboard();
}

void PasteAction::Undo()
{
    for (auto& fig : clipboard) {
        manager_p->DeleteFigure(fig->GetId());
    }
}