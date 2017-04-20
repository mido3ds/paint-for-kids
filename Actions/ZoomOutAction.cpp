#include "ZoomOutAction.h"

ZoomOutAction::ZoomOutAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

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
    zoom_factor = pow(2, manager_p->GetZoom());
}

//Execute the action
void ZoomOutAction::Execute()
{

    int a = zoom_point.x;
    int b = zoom_point.y;

    Output* out_p = manager_p->GetOutput();

    //pointers to shapes
    multiset<CFigure*, CmpFigures>* figs = manager_p->GetFigures();
    CTrngl* trngl_check = NULL;
    CCircle* circle_check = NULL;
    CRectangle* rectangle_check = NULL;
    CLine* line_check = NULL;

    //three points to assign the new points after zooming
    Point p1;
    Point p2;
    Point p3;

    //clearing the drawing area to draw the shapes after zooming
    out_p->ClearDrawArea();

    //for loop to traverse over all the figures and zoom them
    for (auto& fig : (*figs)) {

        //casting the CFigure pointer to determine what shape to draw
        trngl_check = dynamic_cast<CTrngl*>(fig);
        circle_check = dynamic_cast<CCircle*>(fig);
        rectangle_check = dynamic_cast<CRectangle*>(fig);
        line_check = dynamic_cast<CLine*>(fig);

        /*This equation -> P = (zoom_factor*(x-a)+a , zoom_factor*(y-b)+b)
		this equation holds for any point in the drawing area it's based on
		Analytic Geometry where we translate axes to the clicked point multiply
		by the zooming factor and then translate back to the main axes to get
		the new point after zooming the following piece of code check the pointer
		to know which figure to draw calcuate the new points of the shape then
		draw it*/
        if (trngl_check != NULL) {
            //calculating new points
            p1.x = (int(zoom_factor * (trngl_check->p1.x - a))) + a;
            p1.y = (int(zoom_factor * (trngl_check->p1.y - b))) + b;
            p2.x = (int(zoom_factor * (trngl_check->p2.x - a))) + a;
            p2.y = (int(zoom_factor * (trngl_check->p2.y - b))) + b;
            p3.x = (int(zoom_factor * (trngl_check->p3.x - a))) + a;
            p3.y = (int(zoom_factor * (trngl_check->p3.y - b))) + b;
            out_p->DrawTriangle(p1, p2, p3, (GfxInfo(*trngl_check)), trngl_check->IsSelected()); //drawing tringle after zooming

        } else if (circle_check != NULL) {
            //calculating new points
            p1.x = (int(zoom_factor * (circle_check->p1.x - a))) + a;
            p1.y = (int(zoom_factor * (circle_check->p1.y - b))) + b;
            p2.x = (int(zoom_factor * (circle_check->p2.x - a))) + a;
            p2.y = (int(zoom_factor * (circle_check->p2.y - b))) + b;
            out_p->DrawCircle(p1, p2, (GfxInfo(*circle_check)), circle_check->IsSelected()); //drawing circle after zooming

        } else if (rectangle_check != NULL) {
            //calculating new points
            p1.x = (int(zoom_factor * (rectangle_check->p1.x - a))) + a;
            p1.y = (int(zoom_factor * (rectangle_check->p1.y - b))) + b;
            p2.x = (int(zoom_factor * (rectangle_check->p2.x - a))) + a;
            p2.y = (int(zoom_factor * (rectangle_check->p2.y - b))) + b;
            out_p->DrawRect(p1, p2, (GfxInfo(*rectangle_check)), rectangle_check->IsSelected()); //drawing rectangle after zooming

        } else {
            //calculating new points
            p1.x = (int(zoom_factor * (line_check->p1.x - a))) + a;
            p1.y = (int(zoom_factor * (line_check->p1.y - b))) + b;
            p2.x = (int(zoom_factor * (line_check->p2.x - a))) + a;
            p2.y = (int(zoom_factor * (line_check->p2.y - b))) + b;
            out_p->DrawLine(p1, p2, (GfxInfo(*line_check)), line_check->IsSelected()); //drawing line after zooming
        }
    }

    //redrawing bars to avoid any shape be drawn on them
    out_p->ClearStatusBar();
    out_p->CreateDrawToolBar();
    out_p->CreateColorBar();
}

void ZoomOutAction::Undo()
{
    //creating ZoomOutAction customive it to inverse the zoom in action
    ZoomInAction* inverse = new ZoomInAction(manager_p);
    inverse->SetZoomFactor(zoom_factor * 2);
    inverse->SetZoompoint(zoom_point);

    //assigning the action to Action pointer to excute it
    Action* inverse_ptr = &(*inverse);
    manager_p->ExecuteAction(inverse_ptr);
}