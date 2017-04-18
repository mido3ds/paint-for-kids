#include "ApplicationManager.h"

int main()
{
    ActionType act_type;
    ApplicationManager app_manager;

    do {

        act_type = app_manager.GetUserAction();

        app_manager.ExecuteAction(act_type);

		app_manager.UpdateInterface();

    } while (act_type != EXIT);

    return 0;
}