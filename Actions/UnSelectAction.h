#ifndef _UNSELECT_
#define _UNSELECT_

#include "../ApplicationManager.h"
#include "../CMUgraphicsLib/colors.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "Action.h"
#include "SelectAction.h"

class UnselectAction : public Action {
public:
    UnselectAction(ApplicationManager* app_p);
    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Undo();

private:
    Point p;
    CFigure* figure;
};

#endif