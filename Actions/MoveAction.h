#ifndef _MOVEAction_
#define _MOVEAction_

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "Action.h"

class MoveAction : public Action {
public:
    MoveAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Undo();

private:
    Point p; //new center
    Point old; //old center
    bool moved = false;
	deque<CFigure*> moved_figs;
};

#endif