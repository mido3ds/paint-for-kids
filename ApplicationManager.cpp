#include "ApplicationManager.h"
#include "Actions/AddRectAction.h"

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
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
    Action* pAct = NULL;

    //According to Action Type, create the corresponding action object
    switch (ActType) {
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;

		case DRAW_LINE:
			///create AddLineAction here

			break;

		case EXIT:
			///create ExitAction here

			break;

		case STATUS: //a click on the status bar ==> no action
			return;
    }

    //Execute the created action
    if (pAct != NULL) {
        pAct->Execute(); //Execute
        delete pAct; //Action is not needed any more ==> delete it
        pAct = NULL;
    }
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* fig_p)
{
    fig_list.push_back(fig_p);
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(int x, int y) const
{
    //If a figure is found return a pointer to it.
    //if this point (x,y) does not belong to any figure return NULL

    ///Add your code here to search for a figure given a point x,y

    return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
    for (int i = 0; i < fig_list.size(); i++)
        fig_list[i]->Draw(out_p); //Call Draw function (virtual member fn)
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
//Destructor
ApplicationManager::~ApplicationManager()
{
    for (int i = 0; i < fig_list.size(); i++)
        delete fig_list[i];
    delete in_p;
    delete out_p;
}
