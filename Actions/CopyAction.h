#ifndef _COPYAction_
#define _COPYAction_

#include "../ApplicationManager.h"
#include "Action.h"

class CopyAction : public Action {
public:
    CopyAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();

private:
    deque<CFigure*> clipboard;
    bool copied = false;
};

#endif