#include "SelectAction.h"

SelectAction::SelectAction(ApplicationManager* app_p)
    : Action(app_p)
{
}

void SelectAction::ReadActionParameters()
{
     out_p = manager_p->GetOutput();
     in_p = manager_p->GetInput();
    out_p->PrintMessage("Please Click On The Figure/s You Want To Select When Finished Click on Select Icon..");
    
   
}

void SelectAction::Execute()
{
	in_p->GetPointClicked(p.x, p.y);
	p.x = (p.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().x;
	p.y = (p.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().y;
	while (!(p.y < UI.ToolBarHeight && p.y > UI.ToolBarY && p.x > ITM_SELECT*UI.MenuItemWidth && p.x < ITM_SELECT*UI.MenuItemWidth + UI.MenuItemWidth))
	{
		
		selected = manager_p->GetFigure(p.x, p.y);

		if (selected != nullptr && !selected->IsSelected()) {
			selected->SetSelected(true);
			originaldraw = selected->draw_clr;
			manager_p->SetNumSelected(manager_p->GetNumSelected() + 1);
			manager_p->PrintSelectedSize();
			manager_p->UpdateInterface();
		}
		in_p->GetPointClicked(p.x, p.y);
		p.x = (p.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().x;
		p.y = (p.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoom()) + out_p->GetZoomPoint().y;
	}
}
void SelectAction::Undo()
{
	
}
