#include "MultiSelect.h"

MultiSelect::MultiSelect(ApplicationManager * app_p) 
	: Action(app_p)
{
}

void MultiSelect::ReadActionParameters()
{
}

void MultiSelect::Execute()
{
	manager_p->ToggleMultiSelect();

	if (manager_p->IsInMultiSelect())
		manager_p->GetOutput()->PrintMessage("Multi Select Mode Is On", WHITE, true);
	else 
		manager_p->GetOutput()->PrintMessage("Multi Select Mode Is Off");
}

void MultiSelect::Undo()
{
}