#include "CopyAction.h"

CopyAction::CopyAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void CopyAction::ReadActionParameters()
{
	Output* out_p = manager_p->GetOutput();
	out_p->ClearStatusBar();
}

void CopyAction::Execute()
{
    if (manager_p->GetNumSelected() > 0) {
        clipboard = manager_p->GetClipboard();
        manager_p->FillClipboardWithSelected();
        copied = true;
    }
}

void CopyAction::Undo()
{
}