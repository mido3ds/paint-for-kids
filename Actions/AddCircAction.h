#ifndef __AddCircAction_h__
#define __AddCircAction_h__

#include "../ApplicationManager.h"
#include "../Figures/CCircle.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class AddCircAction : public Action {
public:
    AddCircAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();

    virtual ActionType GetActType() {return DRAW_CIRC;}

private:
    CCircle* circ;

    // properities
    unsigned int id;
    GfxInfo gfx;
    Point p1, p2;
};

#endif /* __AddCircAction_h__ */
