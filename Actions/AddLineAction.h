#ifndef __AddLineAction_h__
#define __AddLineAction_h__

#include "Action.h"
#include "../Figures/CLine.h"
#include "../ApplicationManager.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

//Add CLine Action class
class AddLineAction : public Action 
{
public:
    AddLineAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();
    
private:
    CLine* line;
};


#endif  /* __AddLineAction_h__ */

