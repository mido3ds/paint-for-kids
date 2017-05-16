#include "DeleteAction.h"

DeleteAction::DeleteAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void DeleteAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();

	out_p->ClearStatusBar();
    if (manager_p->GetNumSelected() == 0)
        out_p->PrintMessage("No Selected Figures To Delete", WHITE, true);
}

void DeleteAction::Execute()
{
    if (manager_p->GetNumSelected() > 0) 
        clipboard = manager_p->EraseSelected();
}

void DeleteAction::Undo()
{
	for (auto& fig : clipboard)
	{
		manager_p->AddFigure(fig);
		manager_p->SetNumSelected(manager_p->GetNumSelected() + 1);
	}

	clipboard.clear();
}

DeleteAction::~DeleteAction()
{
    for (auto& fig : clipboard)
        delete fig;
}