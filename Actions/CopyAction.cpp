#include "CopyAction.h"

CopyAction::CopyAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void CopyAction::ReadActionParameters()
{
}

void CopyAction::Execute()
{
    if (manager_p->Num_Selected > 0) {
        clipboard = manager_p->GetClipboard();
        manager_p->SetClipboard();
        copied = true;
    }
}

void CopyAction::Undo()
{
    if (copied) {
        manager_p->SetClipboard(clipboard);
        copied = false;
    }
}