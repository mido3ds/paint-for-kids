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
    manager_p->FillClipboardWithSelected();
}

void CopyAction::Undo()
{
}