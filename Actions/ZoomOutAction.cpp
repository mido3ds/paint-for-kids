#include "ZoomOutAction.h"

ZoomOutAction::ZoomOutAction(ApplicationManager* app_p)
	: Action(app_p)
{}

void ZoomOutAction::SetZoomFactor(double z_factor)
{
	zoom_factor = z_factor;
}

void ZoomOutAction::SetZoompoint(Point z_point)
{
	zoom_point = z_point;
}

double ZoomOutAction::GetZoomFactor() const
{
	return zoom_factor;
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

	in_p->GetPointClicked(zoom_point.x, zoom_point.y);

}

//Execute the action
void ZoomOutAction::Execute()
{
	Output* out_p = manager_p->GetOutput();

	out_p->SetZoom(out_p->GetZoom() - 1);
	zoom_factor = pow(2, out_p->GetZoom());
	out_p->SetZoomPoint(zoom_point);

	//clearing the drawing area to draw the shapes after zooming
	out_p->ClearDrawArea();

	//redrawing bars to avoid any shape be drawn on them
	out_p->ClearStatusBar();
	out_p->CreateDrawToolBar();
}


void ZoomOutAction::Undo()
{
	//creating ZoomOutAction customive it to inverse the zoom in action
	ZoomInAction* inverse = new ZoomInAction(manager_p);
	inverse->SetZoomFactor(zoom_factor * 2);
	inverse->SetZoompoint(zoom_point);

	//assigning the action to Action pointer to excute it
	Action* inverse_ptr = &(*inverse);
	//manager_p->ExecuteAction(inverse_ptr);
}