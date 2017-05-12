#include "ApplicationManager.h"

int main()
{
	ActionType action;
	ApplicationManager app;

	do {
		action = app.GetUserAction();
		app.ExecuteAction(action);
		app.UpdateInterface();
	} while (action != EXIT);

	return 0;
}