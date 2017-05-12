#include "ToPlayModeAction.h"

ToPlayModeAction::ToPlayModeAction(ApplicationManager* app_p)
    : Action(app_p , false)
{}

void ToPlayModeAction::ReadActionParameters()
{
}

void ToPlayModeAction::Execute()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("Action: Switch to Play Mode, creating Design tool bar");
    out_p->CreatePlayToolBar();
    out_p->CreateDrawArea();
}

void ToPlayModeAction::Undo()
{
}