#ifndef _UP_
#define _UP_

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class SendUpAction : public Action {
public:
    SendUpAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Undo();

private:
};

#endif