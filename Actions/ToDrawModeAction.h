#ifndef __SwitchDrawMode_H__
#define __SwitchDrawMode_H__

#include "../ApplicationManager.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ToDrawModeAction : public Action {
public:
    ToDrawModeAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();
};

#endif