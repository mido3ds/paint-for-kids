#include "ApplicationManager.h"

int main()
{
	ActionType action;
	ApplicationManager app;

	while (app.IsRunning())
	{
		action = app.GetUserAction();
		app.ExecuteAction(action);
		app.UpdateInterface();
	} 

	return 0;
}