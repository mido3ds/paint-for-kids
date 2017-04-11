#ifndef __AddTrnglAction_h__
#define __AddTrnglAction_h__

#include "Action.h"
#include "../Figures/CTrngl.h"
#include "../ApplicationManager.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

//Add CTrngl Action class
class AddTrnglAction : public Action 
{
public:
    AddTrnglAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();
    
private:
    CTrngl* trngl;
};


#endif  /* __AddTrnglAction_h__ */

