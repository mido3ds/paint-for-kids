#ifndef __AddLineAction_h__
#define __AddLineAction_h__

#include "../ApplicationManager.h"
#include "../Figures/CLine.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class AddLineAction : public Action {
public:
    AddLineAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();

    virtual ActionType GetActType() {return DRAW_LINE;}
private:
    CLine* line;

    unsigned int id;
    GfxInfo gfx;
    Point p1, p2;
};

#endif /* __AddLineAction_h__ */
