#include "ZoomInAction.h"

ZoomInAction::ZoomInAction(ApplicationManager* app_p)
	: Action(app_p)
{}

void ZoomInAction::SetZoomFactor(double z_factor)
{
	zoom_factor = z_factor;
}

void ZoomInAction::SetZoompoint(Point z_point)
{
	zoom_point = z_point;
}

double ZoomInAction::GetZoomFactor() const
{
	return zoom_factor;
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

	in_p->GetPointClicked(zoom_point.x, zoom_point.y);

}

//Execute the action
void ZoomInAction::Execute()
{
	
	Output* out_p = manager_p->GetOutput();

	out_p->SetZoom(out_p->GetZoom() + 1);
	zoom_factor = pow(2, out_p->GetZoom());
	out_p->SetZoomPoint(zoom_point);

	//clearing the drawing area to draw the shapes after zooming
	out_p->ClearDrawArea();

	//redrawing bars to avoid any shape be drawn on them
	out_p->ClearStatusBar();
	out_p->CreateDrawToolBar();

}


void ZoomInAction::Undo()
{
	Output* out_p = manager_p->GetOutput();
	out_p->SetZoom(sqrt(zoom_factor / 2));
	out_p->SetZoomPoint(zoom_point);

}