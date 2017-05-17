#include "ResizeAction.h"

ResizeAction::ResizeAction(ApplicationManager* app_p)
	: Action(app_p)
{}

void ResizeAction::SetResizeFactor(double r_factor)
{
	Output *out_p = manager_p->GetOutput();
	out_p->ClearStatusBar();
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

	int x, y;
	out_p->CreateResize(); // Resize temp tool bar
	out_p->PrintMessage("Choose The Prefered Resize");
	if (manager_p->GetNumSelected() == 1)
	{
		drag = true;
		fig = manager_p->GetSelectedFigure();
		resize_factor = 0;
	}
	else
	{
		do {
			in_p->GetClick(x, y);
		} while (x < UI.TToolBarX || x > 4 * UI.MenuItemWidth || y < UI.TToolBarY || y > UI.TToolBarY + UI.TToolBarHeight);
		int ClickedItemOrder = (x / UI.MenuItemWidth);
		switch (ClickedItemOrder)
		{
		case 0:
			resize_factor = 0.25;
			break;
		case 1:
			resize_factor = 0.5;
			break;
		case 2:
			resize_factor = 2;
			break;
		case 3:
			resize_factor = 4;
			break;
		default:
			resize_factor = 0;
			break;
		}
	}
}

//Execute the action
void ResizeAction::Execute()
{

	Output* out_p = manager_p->GetOutput();
	Point p;
	Corners corner = INVALID;
	GfxInfo info;
	info.border_width = 1;
	info.draw_clr = BLACK;
	info.fill_clr = WHITE;
	info.is_filled = true;

	if (final_fig != nullptr)
	{
		(manager_p->GetFigureById(pre_fig->GetId()))->SetAll(final_fig);
		return;
	}
	
	pre_fig = fig->Copy();

	bool loop = false;
	bool corner_clicked = false;

	Sleep(SECOND);
	if (drag == true)
	{
		out_p->PrintMessage("Resize by dragging to finish press right mouse button", WHITE, true);
		while (true)
		{
			if (out_p->ButtonState(RIGHT_BUTTON, p) == BUTTON_DOWN)
				break;
			fig->DragPoints(out_p, info);
			if (loop == false)
			{
				if (out_p->ButtonState(LEFT_BUTTON, p) == BUTTON_DOWN)
				{
					loop = true;
					//clicked on resize tool bar 
					if (p.x <= UI.TToolBarWidth && p.y <= (UI.TToolBarHeight + UI.MenuItemHeight) && p.y >= UI.TToolBarHeight)
					{
						int ClickedItemOrder = (p.x / UI.MenuItemWidth);
						switch (ClickedItemOrder)
						{
						case 0:
							resize_factor = 0.25;
							break;
						case 1:
							resize_factor = 0.5;
							break;
						case 2:
							resize_factor = 2;
							break;
						case 3:
							resize_factor = 4;
							break;
						default:
							resize_factor = 0;
							break;
						}
						if (fig->CheckResize(resize_factor))
							fig->Resize(resize_factor);
						return;
					}
					corner = fig->GetCornerPoint(p); // getting clicked corner
					loop = true;
					if (corner != INVALID)
						corner_clicked = true;
				}
			}
			else
			{
				//if you raise your finger from mouse button
				if (out_p->ButtonState(LEFT_BUTTON, p) == BUTTON_UP)
				{

					loop = false;
					corner_clicked = false;
					corner = INVALID;

					out_p->CreateResize(); // Resize temp tool bar

				}
				//if you still holding mouse button
				else
				{
					if (corner_clicked)
					{
						if (fig->OutOfDrawingArea(p))
							continue;
						fig->Drag(p, corner);
						manager_p->UpdateInterface(false);
					}
				}
			}
		}
	}
	else
	{
		out_p->ClearDrawArea();
		if (manager_p->CheckResize(resize_factor))
		{
			if (!manager_p->ResizeSelected(resize_factor))
			{
				out_p->PrintMessage("Error no figures selected");
				resize_factor = 1;
			}
		}
	}

	final_fig = (drag == true) ? fig->Copy() : nullptr;

}

void ResizeAction::Undo()
{
	manager_p->ResizeSelected(1 / resize_factor);
	if (pre_fig != nullptr)
		(manager_p->GetFigureById(pre_fig->GetId()))->SetAll(pre_fig);
}

ResizeAction::~ResizeAction()
{
	delete pre_fig;
	delete final_fig;
}