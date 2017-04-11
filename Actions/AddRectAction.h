#ifndef ADD_RECT_ACTION_H
#define ADD_RECT_ACTION_H

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class AddRectAction : public Action {
public:
    AddRectAction(ApplicationManager* app_p);

    //Reads rectangle parameters
    virtual void ReadActionParameters();

    //Add rectangle to the ApplicationManager
    virtual void Execute();

    virtual void Undo();

private:
    CRectangle* rect;

    unsigned int id;
    // TODO add othes
};

#endif