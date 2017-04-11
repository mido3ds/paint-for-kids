#ifndef __AddCircAction_h__
#define __AddCircAction_h__

#include "../ApplicationManager.h"
#include "../Figures/CCircle.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class AddCircAction : public Action {
public:
    AddCircAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

private:
    CCircle* circ;
};

#endif /* __AddCircAction_h__ */
