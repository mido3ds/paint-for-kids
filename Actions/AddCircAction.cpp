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

	out_p->ClearTToolBar();

    out_p->PrintMessage("New Circle: Click at first point");
	
    //Read 1st corner and store in point p1
	do
	{
		in_p->GetPointClicked(p1.x, p1.y);
	} while (p1.y <= UI.ToolBarHeight);

    out_p->PrintMessage("New Circle: Click at second point");

    //Read 2nd corner and store in point p2
	do
	{
		in_p->GetPointClicked(p2.x, p2.y);
	} while (p2.y <= UI.ToolBarHeight);
    
	p1.x = (p1.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().x;
	p1.y = (p1.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().y;

	p2.x = (p2.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().x;
	p2.y = (p2.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().y;

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
void AddCircAction::Execute()
{
    circ = new CCircle(p1, p2, gfx);
    circ->SetId(id);
    if (!circ->OutOfRange(p1)) {
        manager_p->AddFigure(circ);
    } else {
        manager_p->GetOutput()->PrintMessage("The Circle Is Out Of Range");
    }
}

void AddCircAction::Undo()
{
    manager_p->DeleteFigure(id);
}
