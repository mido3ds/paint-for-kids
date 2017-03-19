#ifndef ACTION_H
#define ACTION_H

#include "../DEFS.h"

class ApplicationManager; //forward class declaration

//Base class for all possible actions
class Action 
{
public:
    Action(ApplicationManager* app_p) { manager_p = app_p; } //constructor

    //Reads parameters required for action to execute (code depends on action type)
    virtual void ReadActionParameters() = 0;

    //Execute action (code depends on action type)
    virtual void Execute() = 0;

    //To undo this action (code depends on action type)
    //virtual void Undo() = 0;

    //To redo this action (code depends on action type)
    //virtual void Redo() = 0;

protected:
    ApplicationManager* manager_p; //Actions needs AppMngr to do their job
};

#endif