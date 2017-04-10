#include "ApplicationManager.h"

//Constructor
ApplicationManager::ApplicationManager()
{
    //Create Input and output
    out_p = new Output;
    in_p = out_p->CreateInput();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
    //Ask the input to get the action from the user.
    return in_p->GetUserAction();
}
////////////////////////////////////////////////////////////////////////////////////
// According to Action Type, return the corresponding action object
Action* ApplicationManger::DetectAction(ActionType act_type)
{
    switch (act_type) {
    case DRAW_RECT:
        return new AddRectAction(this);
    case DRAW_CIRC:
        return new AddCircAction(this);
    case DRAW_TRI:
        return new AddTrnglAction(this);
    case DRAW_LINE:
        return new AddLineAction(this);
    case EXIT:
        return new ExitAction(this);
    case TO_PLAY:
        return new SwitchPlayMode(this);
    case TO_DRAW:
        return new SwitchDrawMode(this);
    case STATUS: //a click on the status bar ==> no action
        return nullptr;
    }
}
////////////////////////////////////////////////////////////////////////////////////
// gets action parameters and executes it
void ApplicationManager::ExecuteAction(ActionType act_type)
{
    Action* act_p = DetectAction(act_type);

    if (act_p != nullptr) {
        act_p->ReadActionParameters();
        act_p->Execute();
        delete act_p;
    }
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* fig_p)
{
    figs.insert(fig_p);
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(int x, int y) const
{
    //If a figure is found return a pointer to it.
    //if this point (x,y) does not belong to any figure return NULL

    ///Add your code here to search for a figure given a point x,y

    return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
// According to given string, return the corresponding Figure object
CFigure* ApplicationManger::DetectFigure(string fig_name)
{
    switch (fig_name) {
    case "RECTANGLE":
        return new CRectangle();
    case "CIRCLE":
        return new CCircle();
    case "TRIANGLE":
        return new CTrngl();
    case "LINE":
        return new CLine();
    default:
        throw - 1;
    }
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
    for (auto& fig : figs)
        fig->Draw(out_p); //Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input* ApplicationManager::GetInput() const
{
    return in_p;
}
//Return a pointer to the output
Output* ApplicationManager::GetOutput() const
{
    return out_p;
}
////////////////////////////////////////////////////////////////////////////////////
// iterate through all figures
// call save for each one
void ApplicationManager::SaveAll(ofstream& out_file)
{
    // TODO
    out_file << UI.DrawColor << ' ' << UI.FillColor << ' ' << UI.BkGrndColor << '\n';
    out_file << figs.size() << '\n';

    for (auto& fig : figs)
        fig->Save(out_file);
}
// iterate through lines and make the apropriate figure
// call load for the figure
void ApplicationManager::LoadAll(ifstream& in_file)
{
    // TODO
    int size = 0;
    string fig_name;
    CFigure* fig = nullptr;

    in_file >> UI.DrawColor >> UI.FillColor >> UI.BkGrndColor;
    in_file >> size;

    for (int i = 0; i < size; i++) {
        in_file >> fig_name;
        fig = DetectFigure(fig_name);
        fig->Load(in_file);

        figs.insert(fig);
    }
}

////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
    for (auto& fig : figs)
        delete fig;
    delete in_p;
    delete out_p;
}
