#ifndef _CUTAction_
#define _CUTAction_

#include "../ApplicationManager.h"
#include "Action.h"

class CutAction : public Action {
public:
    CutAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();

private:
    deque<CFigure*> clipboard; //to store old clipboard
    deque<CFigure*> cutAction;
    bool cutActioned = false;
};

#endif