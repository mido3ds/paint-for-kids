#include "ExitAction.h"

ExitAction::ExitAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void ExitAction::ReadActionParameters()
{
    int x, y;
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("Exitting: click at any point to exit");
    in_p->GetPointClicked(x, y);
}

//Execute the action
void ExitAction::Execute()
{
    // it will exit automatically from the main function
    // look at do-while at Main.cpp
}

void ExitAction::Undo()
{
}