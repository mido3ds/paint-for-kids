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

    out_p->PrintMessage("New triangle: Click at first point");

    //Read 1st corner and store in point p1
	in_p->GetClick(p1.x, p1.y);

    out_p->PrintMessage("New triangle: Click at second corner");

    //Read 2nd corner and store in point p2
	in_p->GetClick(p2.x, p2.y);

    out_p->PrintMessage("New triangle: Click at third corner");

    //Read 2nd corner and store in point p2
	in_p->GetClick(p3.x, p3.y);
    
	p1.x = (int)((p1.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().x);
	p1.y = (int)((p1.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().y);

	p2.x = (int)((p2.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().x);
	p2.y = (int)((p2.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().y);

	p3.x = (int)((p3.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().x);
	p3.y = (int)((p3.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().y);

    gfx.is_filled = UI.IsFilled; //default is not filled
    gfx.draw_clr = out_p->GetDrawColor();
    gfx.fill_clr = out_p->GetFillColor();
    gfx.border_width = out_p->GetPenWidth();

    out_p->ClearStatusBar();

    id = manager_p->GenerateNextId();
}

void AddTrnglAction::Execute(bool redo)
{
    trngl = new CTrngl(p1, p2, p3, gfx);
    trngl->SetId(id);

    if (!trngl->IsOutOfRange(p1, p2, p3))
        manager_p->AddFigure(trngl);
    else
        manager_p->GetOutput()->PrintMessage("The Triangle Is Out Of Range", RED, true);
}

void AddTrnglAction::Undo()
{
    manager_p->DeleteFigure(id);
}