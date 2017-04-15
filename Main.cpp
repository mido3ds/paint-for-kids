#include "ApplicationManager.h"

int main()
{
    ActionType act_type;
    ApplicationManager AppManager;

    do {
        act_type = AppManager.GetUserAction();
        AppManager.ExecuteAction(act_type);

		if (AppManager.GetZoom() > 0)
		{
			ZoomInAction zoom_in(&AppManager);
			zoom_in.SetZoomFactor(pow(2, AppManager.GetZoom()));
			zoom_in.SetZoompoint(AppManager.GetManagerZoomPoint());
			zoom_in.Execute();
		}
		else if (AppManager.GetZoom() < 0)
		{
			ZoomOutAction zoom_out(&AppManager);
			zoom_out.SetZoomFactor(pow(2, AppManager.GetZoom()));
			zoom_out.SetZoompoint(AppManager.GetManagerZoomPoint());
			zoom_out.Execute();
		}
		else
			AppManager.UpdateInterface();

    } while (act_type != EXIT);

    return 0;
}