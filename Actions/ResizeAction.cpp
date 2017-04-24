#include "ResizeAction.h"

ResizeAction::ResizeAction(ApplicationManager* app_p)
	: Action(app_p)
{}

void ResizeAction::SetResizeFactor(double r_factor)
{
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

	out_p->ClearTToolBar();

	string data;
	char* val = NULL;
	do
	{
		data = in_p->GetString(out_p);
		resize_factor = strtod(data.c_str(), &val);
	} while (*val == data[0] || resize_factor <= 0);
}

//Execute the action
void ResizeAction::Execute()
{

	Output* out_p = manager_p->GetOutput();


	//clearing the drawing area to remove the old shape and draw a new one with the new size
	out_p->ClearDrawArea();

	if (!manager_p->ResizeSelected(resize_factor))
		out_p->PrintMessage("Error no figures selected");
}


void ResizeAction::Undo()
{
	// TODO: 
}