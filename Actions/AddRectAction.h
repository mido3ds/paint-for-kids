#ifndef ADD_RECT_ACTION_H
#define ADD_RECT_ACTION_H

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

//Add CRectangle Action class
class AddRectAction : public Action {
public:
    AddRectAction(ApplicationManager* app_p);

    //Reads rectangle parameters
    virtual void ReadActionParameters();

    //Add rectangle to the ApplicationManager
    virtual void Execute();

private:
    CRectangle* rect;
};

#endif