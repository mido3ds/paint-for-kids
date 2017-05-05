#include "AddLineAction.h"

AddLineAction::AddLineAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void AddLineAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("New Line: Click at first point");

    //Read 1st corner and store in point p1
	in_p->GetClickPoint(p1.x, p1.y);

    out_p->PrintMessage("New Line: Click at second corner");

    //Read 2nd corner and store in point p2
	in_p->GetClickPoint(p2.x, p2.y);

	p1.x = (p1.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().x;
	p1.y = (p1.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().y;

	p2.x = (p2.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().x;
	p2.y = (p2.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().y;

    gfx.is_filled = false; //default is not filled
    //get drawing, filling colors and pen width from the interface
    gfx.draw_clr = out_p->GetDrawColor();
    gfx.fill_clr = out_p->GetFillColor();
    gfx.border_width = out_p->GetPenWidth();

    out_p->ClearStatusBar();

    id = manager_p->GenerateNextId();
}

//Execute the action
void AddLineAction::Execute()
{
    //Add the lineangle to the list of figures
    line = new CLine(p1, p2, gfx);
    line->SetId(id);
    if (!line->IsOutOfRange(p1, p2)) {
        manager_p->AddFigure(line);
    } else {
        manager_p->GetOutput()->PrintMessage("The Line Is Out Of Range");
    }
}

void AddLineAction::Undo()
{
    manager_p->DeleteFigure(id);
}
