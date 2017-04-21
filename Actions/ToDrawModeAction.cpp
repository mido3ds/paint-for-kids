#include "ToDrawModeAction.h"

ToDrawModeAction::ToDrawModeAction(ApplicationManager* app_p)
    : Action(app_p, false)
{
}

void ToDrawModeAction::ReadActionParameters()
{
}

void ToDrawModeAction::Execute()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* out_p = manager_p->GetOutput();
    Input* in_p = manager_p->GetInput();

    out_p->PrintMessage(
        "Action: Switch to Draw Mode, creating simualtion tool bar");
    out_p->CreateDrawToolBar();
    out_p->CreateDrawArea();
}

void ToDrawModeAction::Undo()
{
    manager_p->ExecuteAction(TO_PLAY);
}