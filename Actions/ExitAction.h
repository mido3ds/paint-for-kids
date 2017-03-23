#ifndef __ExitAction_h__
#define __ExitAction_h__

#include "Action.h"
#include "../ApplicationManager.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

//Add CLine Action class
class ExitAction : public Action 
{
public:
    ExitAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();
};


#endif  /* __ExitAction_h__ */

