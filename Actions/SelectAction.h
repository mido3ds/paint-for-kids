#ifndef __SelectAction_h__
#define __SelectAction_h__

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
    CFigure* selected;
    Point p;
    //color originalfill;
    color originaldraw;
	Output* out_p;
	Input* in_p;
};

#endif /* __SelectAction_h__ */