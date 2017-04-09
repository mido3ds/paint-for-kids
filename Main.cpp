#include "ApplicationManager.h"

int main()
{
    ActionType ActType;
    ApplicationManager AppManager;

    do 
    {
        ActType = AppManager.GetUserAction();
        AppManager.ExecuteAction(ActType);
        AppManager.UpdateInterface();
    } 
    while (ActType != EXIT);

    return 0;
}