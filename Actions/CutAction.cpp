#include "CutAction.h"

CutAction::CutAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void CutAction::ReadActionParameters()
{
}

void CutAction::Execute()
{
    if (manager_p->GetNumSelected() > 0) {
        clipboard = manager_p->GetClipboard();
        manager_p->FillClipboardWithSelected();
        cutAction = manager_p->DeleteSelected();
        cutActioned = true;
    }
}

void CutAction::Undo()
{
}