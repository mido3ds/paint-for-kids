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
	if (manager_p->GetMultiSelect()){
		manager_p->GetOutput()->PrintMessage("Multi Select Mode Is On");
	}
	else {
		manager_p->GetOutput()->PrintMessage("Multi Select Mode Is Off");
	}
}

void MultiSelect::Undo()
{
}
