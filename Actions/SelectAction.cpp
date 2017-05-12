

#include "SelectAction.h"

SelectAction::SelectAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void SelectAction::ReadActionParameters()
{
	out_p = manager_p->GetOutput();
	in_p = manager_p->GetInput();
	//out_p->PrintMessage("Please Click On The Figure/s You Want To Select When Finished Click on Select Icon..");
}

void SelectAction::Execute()
{
	p = in_p->GetLastClickedPoint();
	p.x = (p.x - out_p->GetZoomPoint().x) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().x;
	p.y = (p.y - out_p->GetZoomPoint().y) / pow(2, out_p->GetZoomScale()) + out_p->GetZoomPoint().y;
	if (manager_p->GetMultiSelect())
	{
		// If The Mode Is Multi Select Mode
		selected = manager_p->GetFigure(p.x, p.y);

		if (selected) {
			if (!selected->IsSelected()) {
				selected->SetSelected(true);
				originaldraw = selected->GetDrawColor();		//Why This???
				manager_p->SetNumSelected(manager_p->GetNumSelected() + 1);
				manager_p->PrintSelectedSize();
			}
			else {
				selected->SetSelected(false);
				originaldraw = selected->GetDrawColor();		//Why This???
				manager_p->SetNumSelected(manager_p->GetNumSelected() - 1);
				manager_p->PrintSelectedSize();
			}
		}
		else {
			manager_p->UnselectAll();
			out_p->PrintMessage("Unselect All Figures");
		}
	}
	else {
		
		selected = manager_p->GetFigure(p.x, p.y);
		if (selected) {
			if (!selected->IsSelected()) {
				manager_p->UnselectAll();
				selected->SetSelected(true);
				originaldraw = selected->GetDrawColor();		//Why This???
				manager_p->SetNumSelected(1);
				manager_p->PrintSelectedSize();
			}
			else {
				selected->SetSelected(false);
				originaldraw = selected->GetDrawColor();		//Why This???
				manager_p->SetNumSelected(0);
				manager_p->PrintSelectedSize();
			}
		}
		else {
			manager_p->UnselectAll();
			out_p->PrintMessage("Unselect All Figures");
		}
	}
}



void SelectAction::Undo()
{
}

