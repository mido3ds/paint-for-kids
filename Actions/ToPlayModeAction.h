#ifndef __SwitchPlayMode_H__
#define __SwitchPlayMode_H__

#include "../ApplicationManager.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ToPlayModeAction : public Action {
public:
    ToPlayModeAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();

    
};

#endif