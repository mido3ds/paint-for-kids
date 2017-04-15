#ifndef __UndoAction_h__
#define __UndoAction_h__

#include "../ApplicationManager.h"
#include "Action.h"

class UndoAction : public Action {
public:
    UndoAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();

    
};

#endif /* __UndoAction_h__ */
