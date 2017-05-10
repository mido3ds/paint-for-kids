#ifndef __DraggingAction_h__
#define __DraggingAction_h__

#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "Action.h"
#include <fstream>

class DraggingAction : public Action {
public:
    DraggingAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Undo();

    void ResizeByDragging();
    void MoveByDragging();

private:
    Input* in_p;
    Point p;
    CFigure* fig;
};

#endif /* __DraggingAction_h__ */