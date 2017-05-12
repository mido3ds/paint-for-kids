#include "DrawFigItems.h"

DrawFigItems::DrawFigItems(ApplicationManager * app_p) :Action(app_p, false)
{
}

void DrawFigItems::ReadActionParameters()
{
	Input *in_p = manager_p->GetInput();
	Output *out_p = manager_p->GetOutput();
	out_p->ClearStatusBar();
	out_p->CreateFigItems();
	act = in_p->GetUserAction();
}

void DrawFigItems::Execute()
{
	manager_p->ExecuteAction(act);
}

void DrawFigItems::Undo()
{
}
