#include "ToPlayModeAction.h"

ToPlayModeAction::ToPlayModeAction(ApplicationManager* app_p)
    : Action(app_p , false)
{}

void ToPlayModeAction::ReadActionParameters()
{
}

void ToPlayModeAction::Execute()
{
    Output* out_p = manager_p->GetOutput();

    out_p->PrintMessage("Action: Switch to Play Mode, creating Design tool bar", WHITE, true);
    out_p->CreatePlayToolBar();
    out_p->CreateDrawArea();
}

void ToPlayModeAction::Undo()
{
}