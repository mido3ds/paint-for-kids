#include "SwitchDrawMode.h"

SwitchDrawMode::SwitchDrawMode(ApplicationManager* app_p)
    : Action(app_p)
{
}

void SwitchDrawMode::ReadActionParameters()
{
}

void SwitchDrawMode::Execute()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage(
        "Action: Switch to Draw Mode, creating simualtion tool bar");
    out_p->CreateDrawToolBar();
    out_p->CreateDrawArea();
}

void SwitchDrawMode::Undo()
{
    
}