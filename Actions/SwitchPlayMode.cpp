#include "SwitchPlayMode.h"

SwitchPlayMode::SwitchPlayMode(ApplicationManager* app_p)
    : Action(app_p)
{
}

void SwitchPlayMode::ReadActionParameters()
{
}

void SwitchPlayMode::Execute()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage("Action: Switch to Play Mode, creating Design tool bar");
    out_p->CreatePlayToolBar();
    out_p->CreatePlayArea();
}
