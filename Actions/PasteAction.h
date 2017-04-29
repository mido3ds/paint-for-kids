#ifndef _PASTEAction_
#define _PASTEAction_

#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "Action.h"
#include "MoveAction.h"

class PasteAction : public Action {
public:
    PasteAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Undo();

private:
    deque<CFigure*> clipboard;
    Point p;
};
#endif
