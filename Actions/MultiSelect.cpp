#include "MultiSelect.h"

MultiSelect::MultiSelect(ApplicationManager * app_p) 
	: Action(app_p)
{
}

void MultiSelect::ReadActionParameters()
{
}

void MultiSelect::Execute(bool redo)
{
	manager_p->ToggleMultiSelect();

	if (manager_p->IsInMultiSelect())
		manager_p->GetOutput()->PrintMessage("Multi Select Mode Is On", WHITE, true);
	else 
		manager_p->GetOutput()->PrintMessage("Multi Select Mode Is Off", WHITE, true);
}

void MultiSelect::Undo()
{
}