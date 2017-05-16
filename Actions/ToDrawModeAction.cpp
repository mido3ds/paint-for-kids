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
    Output* out_p = manager_p->GetOutput();

    out_p->PrintMessage("Action: Switch to Draw Mode, creating simualtion tool bar", WHITE, true);
    out_p->CreateDrawToolBar();
    out_p->CreateDrawArea();
}

void ToDrawModeAction::Undo()
{
}