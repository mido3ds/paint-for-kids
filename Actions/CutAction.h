#ifndef _CUTAction_
#define _CUTAction_

#include "../ApplicationManager.h"
#include "Action.h"

class CutAction : public Action {
public:
    CutAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void ExecutActione();

    virtual void Undo();

private:
    multiset<CFigure*, CmpFigures> clipboard; //to store old clipboard
    vector<CFigure*> cutAction;
    bool cutActioned = false;
};

#endif