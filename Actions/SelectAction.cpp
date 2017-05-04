#include "SelectAction.h"

SelectAction::SelectAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void SelectAction::ReadActionParameters()
{
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("Please Click On The Figure/s You Want To Select When Finished Click on Select Icon..");
    in_p->GetClickPoint(p.x, p.y);
	p.x = (p.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().x;
	p.y = (p.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().y;

    out_p->ClearStatusBar();
}

void SelectAction::Execute()
{

    selected = manager_p->GetFigure(p.x, p.y);

    if (selected != nullptr && !selected->IsSelected()) {
		selected->SetSelected(true);
		originaldraw = selected->GetDrawColor();

		manager_p->SetNumSelected(manager_p->GetNumSelected() + 1);
        manager_p->PrintSelectedSize();
    }
}

void SelectAction::Undo()
{
}