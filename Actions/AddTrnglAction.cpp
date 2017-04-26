#include "AddTrnglAction.h"

AddTrnglAction::AddTrnglAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void AddTrnglAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

	out_p->ClearTToolBar();

    out_p->PrintMessage("New triangle: Click at first point");

    //Read 1st corner and store in point p1
	in_p->GetPointClicked(p1.x, p1.y);

    out_p->PrintMessage("New triangle: Click at second corner");

    //Read 2nd corner and store in point p2
	in_p->GetPointClicked(p2.x, p2.y);

    out_p->PrintMessage("New triangle: Click at third corner");

    //Read 2nd corner and store in point p2
	in_p->GetPointClicked(p3.x, p3.y);
    
	p1.x = (p1.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().x;
	p1.y = (p1.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().y;

	p2.x = (p2.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().x;
	p2.y = (p2.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().y;

	p3.x = (p3.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().x;
	p3.y = (p3.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().y;

    gfx.is_filled = false; //default is not filled
    //get drawing, filling colors and pen width from the interface
    gfx.draw_clr = out_p->GetCrntDrawColor();
    gfx.fill_clr = out_p->GetCrntFillColor();
    gfx.border_width = out_p->GetCrntPenWidth();

    out_p->ClearStatusBar();
    out_p->ClearTToolBar();

    id = manager_p->GenerateNextId();
}

//Execute the action
void AddTrnglAction::Execute()
{
    trngl = new CTrngl(p1, p2, p3, gfx);
    trngl->SetId(id);
    if (!trngl->OutOfRange(p1, p2, p3)) {
        manager_p->AddFigure(trngl);
    } else {
        manager_p->GetOutput()->PrintMessage("The Triangle Is Out Of Range");
    }
}

void AddTrnglAction::Undo()
{
    manager_p->DeleteFigure(id);
}