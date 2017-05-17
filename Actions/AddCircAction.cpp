#include "AddCircAction.h"

AddCircAction::AddCircAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void AddCircAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("New Circle: Click at first point");
	
    //Read 1st corner and store in point p1
	in_p->GetClick(p1.x, p1.y);

    out_p->PrintMessage("New Circle: Click at second point");

    //Read 2nd corner and store in point p2
	in_p->GetClick(p2.x, p2.y);
    
	p1.x = (p1.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().x;
	p1.y = (p1.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().y;

	p2.x = (p2.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().x;
	p2.y = (p2.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().y;

    gfx.is_filled = UI.IsFilled; //default is not filled

    //get drawing, filling colors and pen width from the interface
    gfx.draw_clr = out_p->GetDrawColor();
    gfx.fill_clr = out_p->GetFillColor();
    gfx.border_width = out_p->GetPenWidth();

    out_p->ClearStatusBar();

	radius = static_cast<int>(
		sqrt(pow((p2.y - p1.y), 2) + pow((p2.x - p1.x), 2))
	);

    id = manager_p->GenerateNextId();
}

void AddCircAction::Execute()
{
    circ = new CCircle(p1, radius, gfx);
    circ->SetId(id);
    if (!circ->IsOutOfRange(p1)) {
        manager_p->AddFigure(circ);
    } else {
        manager_p->GetOutput()->PrintMessage("The Circle Is Out Of Range", RED, true);
    }
}

void AddCircAction::Undo()
{
    manager_p->DeleteFigure(id);
}