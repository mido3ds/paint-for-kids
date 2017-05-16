#include "ZoomOutAction.h"

ZoomOutAction::ZoomOutAction(ApplicationManager* app_p)
	: Action(app_p)
{}

void ZoomOutAction::SetZoompoint(Point z_point)
{
	zoom_point = z_point;
}

Point ZoomOutAction::GetZoomPoint() const
{
	return zoom_point;
}

void ZoomOutAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* out_p = manager_p->GetOutput();
	Input* in_p = manager_p->GetInput();

	out_p->PrintMessage("ZoomOut: Click at the point you want to zoom");

	in_p->GetClick(zoom_point.x, zoom_point.y);
	out_p->ClearStatusBar();
}

//Execute the action
void ZoomOutAction::Execute()
{
	Output* out_p = manager_p->GetOutput();

	pre_zoom_point = out_p->GetZoomPoint();
	out_p->SetZoomScale(out_p->GetZoomScale() - 1);
	out_p->SetZoomPoint(zoom_point);
}


void ZoomOutAction::Undo()
{
	Output* out_p = manager_p->GetOutput();
	out_p->SetZoomScale(out_p->GetZoomScale() + 1);
	out_p->SetZoomPoint(pre_zoom_point);
}