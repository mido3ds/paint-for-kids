#include "ZoomInAction.h"

ZoomInAction::ZoomInAction(ApplicationManager* app_p)
	: Action(app_p)
{}

void ZoomInAction::SetZoompoint(Point z_point)
{
	zoom_point = z_point;
}

Point ZoomInAction::GetZoomPoint() const
{
	return zoom_point;
}

void ZoomInAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* out_p = manager_p->GetOutput();
	Input* in_p = manager_p->GetInput();

	out_p->PrintMessage("ZoomIn: Click at the point you want to zoom");

	//in_p->GetPointClicked(zoom_point.x, zoom_point.y);
	in_p->GetClickPoint(zoom_point.x, zoom_point.y);
	out_p->ClearStatusBar();
}

//Execute the action
void ZoomInAction::Execute()
{
	Output* out_p = manager_p->GetOutput();

	pre_zoom_point = out_p->GetZoomPoint();
	out_p->SetZoom(out_p->GetZoom() + 1);
	out_p->SetZoomPoint(zoom_point);
}

void ZoomInAction::Undo()
{
	Output* out_p = manager_p->GetOutput();
	out_p->SetZoom(out_p->GetZoom() - 1);
	out_p->SetZoomPoint(pre_zoom_point);
}