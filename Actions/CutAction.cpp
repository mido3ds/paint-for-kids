#include "CutAction.h"

CutAction::CutAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void CutAction::ReadActionParameters()
{
}

void CutAction::Execute()
{
    if (manager_p->GetNumSelected() > 0) {
        clipboard = manager_p->GetClipboard();
        manager_p->SetClipboard();
        cutAction = manager_p->DeleteSelected();
        cutActioned = true;
    }
}

void CutAction::Undo()
{
    if (cutActioned) {
        for (int i = 0; i < cutAction.size(); i++) {
            manager_p->AddFigure(cutAction[i]);
        }
        manager_p->SetClipboard(clipboard);
        cutActioned = false;
    }
}