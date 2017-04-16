#ifndef __RedoAction_h__
#define __RedoAction_h__

#include "../ApplicationManager.h"
#include "Action.h"

class RedoAction : public Action {
public:
    RedoAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();
};

#endif /* __RedoAction_h__ */
