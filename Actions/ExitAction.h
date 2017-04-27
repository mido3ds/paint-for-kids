#ifndef __ExitAction_h__
#define __ExitAction_h__

#include "../ApplicationManager.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ExitAction : public Action {
public:
    ExitAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();
};

#endif /* __ExitAction_h__ */
