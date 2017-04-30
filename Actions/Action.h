#ifndef ACTION_H
#define ACTION_H

#include "../DEFS.h"
#include <typeinfo>

class ApplicationManager; //forward class declaration

//Base class for all possible actions
class Action {
public:
    Action(ApplicationManager* app_p, bool given_can_undo = true)
		: can_undo(given_can_undo), manager_p(app_p)
	{}

    //Reads parameters required for action to execute (code depends on action type)
    virtual void ReadActionParameters() = 0;

    //Execute action (code depends on action type)
    virtual void Execute() = 0;

    //To undo this action (code depends on action type)
    virtual void Undo() = 0;

    // is this action can be undoed? determine whether to add it to history or not
    bool CanUndo() { return can_undo; }

    // given object from action and class action
    // returns true if this object is instance of this action
    // used to detect what is this action during run-time
    template <class action_class>
    static bool IsFromAction(const Action* object)
    {
        return typeid(*object) == typeid(action_class);
    }

protected:
    ApplicationManager* manager_p; //Actions needs AppMngr to do their job
    const bool can_undo; // action can be undoed by default
};

#endif