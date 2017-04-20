#include "ResizeAction.h"

ResizeAction::ResizeAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void ResizeAction::SetResizeFactor(double r_factor)
{
    resize_factor = r_factor;
}

void ResizeAction::SetCenter(Point r_center)
{
    center = r_center;
}

void ResizeAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    string data;
    char* val = NULL;
    do {
        data = in_p->GetString(out_p);
        resize_factor = strtod(data.c_str(), &val);
    } while (*val == data[0] || resize_factor <= 0);

    /*string data;
	char* val = NULL;
	do
	{
		data = out_p->CreateGetDataWind("Resize Factor");
		resize_factor = strtod(data.c_str(), &val);
	} while (*val == data[0] || resize_factor <= 0);
	manager_p->UpdateInterface();*/
}

//Execute the action
void ResizeAction::Execute()
{

    Output* out_p = manager_p->GetOutput();

    //pointers to shapes
    multiset<CFigure*, CmpFigures>* figs = manager_p->GetFigures();
    CTrngl* trngl_check = NULL;
    CCircle* circle_check = NULL;
    CRectangle* rectangle_check = NULL;
    CLine* line_check = NULL;

    //clearing the drawing area to remove the old shape and draw a new one with the new size
    out_p->ClearDrawArea();

    /*This equation -> P = (zoom_factor*(x-a)+a , zoom_factor*(y-b)+b)
	this equation holds for any point in the drawing area it's based on
	Analytic Geometry where we translate axes to the clicked point multiply
	by the zooming factor and then translate back to the main axes to get
	the new point after zooming the following piece of code check the pointer
	to know which figure to draw calcuate the new points of the shape then
	draw it...resizing is a permenant zooming for a figure from its center*/
    for (auto& fig : (*figs)) {
        //check being selected (only selected shapes will be resized)
        if (!(fig->IsSelected()))
            continue;

        //casting to determine which figure would be resized
        trngl_check = dynamic_cast<CTrngl*>(fig);
        circle_check = dynamic_cast<CCircle*>(fig);
        rectangle_check = dynamic_cast<CRectangle*>(fig);
        line_check = dynamic_cast<CLine*>(fig);

        if (trngl_check != NULL) {
            //calculating center of tringle
            Point p1((trngl_check->p1.x + trngl_check->p2.x) / 2, (trngl_check->p1.y + trngl_check->p2.y) / 2);
            Point p2((trngl_check->p2.x + trngl_check->p3.x) / 2, (trngl_check->p2.y + trngl_check->p3.y) / 2);
            int m1 = (p1.y - trngl_check->p3.y) / (p1.x - trngl_check->p3.x);
            int m2 = (p2.y - trngl_check->p1.y) / (p2.x - trngl_check->p1.x);

            //assigning resizing point to the center of the tringle
            center.x = (m1 * p1.x - m2 * p2.x + p2.y - p1.y) / (m1 - m2);
            center.y = m2 * (center.x - p2.x) + p2.y;

            //resizing tringle by moving points to it's new location
            trngl_check->p1.x = (int(resize_factor * (trngl_check->p1.x - center.x))) + center.x;
            trngl_check->p1.y = (int(resize_factor * (trngl_check->p1.y - center.y))) + center.y;
            trngl_check->p2.x = (int(resize_factor * (trngl_check->p2.x - center.x))) + center.x;
            trngl_check->p2.y = (int(resize_factor * (trngl_check->p2.y - center.y))) + center.y;
            trngl_check->p3.x = (int(resize_factor * (trngl_check->p3.x - center.x))) + center.x;
            trngl_check->p3.y = (int(resize_factor * (trngl_check->p3.y - center.y))) + center.y;
        } else if (circle_check != NULL) {
            //circle center is the first point no need to calculate it
            center.x = circle_check->p1.x;
            center.y = circle_check->p1.y;

            //resizing circle by moving points to it's new location
            circle_check->p2.x = (int(resize_factor * (circle_check->p2.x - center.x))) + center.x;
            circle_check->p2.y = (int(resize_factor * (circle_check->p2.y - center.y))) + center.y;
        } else if (rectangle_check != NULL) {
            //rectangle center is the mid point of its two points
            center.x = (rectangle_check->p1.x + rectangle_check->p2.x) / 2;
            center.y = (rectangle_check->p1.y + rectangle_check->p2.y) / 2;

            //resizing rectangle by moving points to it's new location
            rectangle_check->p1.x = (int(resize_factor * (rectangle_check->p1.x - center.x))) + center.x;
            rectangle_check->p1.y = (int(resize_factor * (rectangle_check->p1.y - center.y))) + center.y;
            rectangle_check->p2.x = (int(resize_factor * (rectangle_check->p2.x - center.x))) + center.x;
            rectangle_check->p2.y = (int(resize_factor * (rectangle_check->p2.y - center.y))) + center.y;
        } else {
            //line center is the mid of its two points
            center.x = (line_check->p1.x + line_check->p2.x) / 2;
            center.y = (line_check->p1.y + line_check->p2.y) / 2;

            //resizing line by moving points to it's new location
            line_check->p1.x = (int(resize_factor * (line_check->p1.x - center.x))) + center.x;
            line_check->p1.y = (int(resize_factor * (line_check->p1.y - center.y))) + center.y;
            line_check->p2.x = (int(resize_factor * (line_check->p2.x - center.x))) + center.x;
            line_check->p2.y = (int(resize_factor * (line_check->p2.y - center.y))) + center.y;
        }
    }

    //redrawing bars to avoid any shape be drawn on them
    out_p->ClearStatusBar();
    out_p->CreateDrawToolBar();
    out_p->CreateColorBar();
}

void ResizeAction::Undo()
{
    /*select previously selected items depends on select action*/

    //creating ZoomOutAction customive it to inverse the zoom in action
    ResizeAction* inverse = new ResizeAction(manager_p);
    inverse->SetResizeFactor(1 / this->resize_factor);
    //assigning the action to Action pointer to excute it
    Action* inverse_ptr = &(*inverse);
    manager_p->ExecuteAction(inverse_ptr);
}