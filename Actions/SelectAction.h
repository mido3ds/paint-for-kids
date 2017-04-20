#ifndef _SELECT_
#define _SELECT_

#include "../ApplicationManager.h"
#include "../CMUgraphicsLib/colors.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class SelectAction : public Action {
public:
    SelectAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Undo();

private:
    CFigure* Selected;
    Point p;
    color originalfill;
    color originaldraw;
};

#endif