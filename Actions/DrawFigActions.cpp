#include "DrawFigActions.h"

DrawFigActions::DrawFigActions(ApplicationManager * app_p) :Action(app_p, false)
{
}

void DrawFigActions::ReadActionParameters()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	out_p->CreateFigActions();
	act = in_p->GetUserAction();
}

void DrawFigActions::Execute()
{
	manager_p->ExecuteAction(act);
}

void DrawFigActions::Undo()
{
}
