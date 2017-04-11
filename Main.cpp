#include "ApplicationManager.h"

int main()
{
    ActionType act_type;
    ApplicationManager AppManager;

    do {
        act_type = AppManager.GetUserAction();
        AppManager.ExecuteAction(act_type);
        AppManager.UpdateInterface();
    } while (act_type != EXIT);

    return 0;
}