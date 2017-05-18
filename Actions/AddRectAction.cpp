#include "AddRectAction.h"

AddRectAction::AddRectAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void AddRectAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("New Rectangle: Click at first corner");

    //Read 1st corner and store in point p1
	in_p->GetClick(p1.x, p1.y);

    out_p->PrintMessage("New Rectangle: Click at second corner");

    //Read 2nd corner and store in point p2
	in_p->GetClick(p2.x, p2.y);

	p1.x = (int)((p1.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().x);
	p1.y = (int)((p1.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().y);

	p2.x = (int)((p2.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().x);
	p2.y = (int)((p2.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().y);

    gfx.is_filled = UI.IsFilled; //default is not filled
    
    //get drawing, filling colors and pen width from the interface
    gfx.draw_clr = out_p->GetDrawColor();
    gfx.fill_clr = out_p->GetFillColor();
    gfx.border_width = out_p->GetPenWidth();

    out_p->ClearStatusBar();

    id = manager_p->GenerateNextId();
}

void AddRectAction::Execute(bool redo)
{
    rect = new CRectangle(p1, p2, gfx);
    rect->SetId(id);

    if (!rect->IsOutOfRange(p1, p2))
        manager_p->AddFigure(rect);
    else
        manager_p->GetOutput()->PrintMessage("The Rectangle Is Out Of Range", RED, true);
}

void AddRectAction::Undo()
{
    manager_p->DeleteFigure(id);
}