/* 
    Base class for all possible actions 
*/
#ifndef ACTION_H
#define ACTION_H

#include "../DEFS.h"

class ApplicationManager; //forward class declaration
class Action 
{
public:
    Action(ApplicationManager* app_p, bool given_can_undo = true)
		: can_undo(given_can_undo), manager_p(app_p)
	{}

    virtual void ReadActionParameters() = 0;
    virtual void Execute(bool redo = false) = 0;
    virtual void Undo() = 0;

    bool CanUndo() { return can_undo; }

protected:
    ApplicationManager* manager_p;
    const bool can_undo; // action can be undoed by default
};

#endif