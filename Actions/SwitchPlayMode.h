#ifndef __SwitchPlayMode_H__
#define __SwitchPlayMode_H__

#include "../ApplicationManager.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class SwitchPlayMode : public Action {
public:
    SwitchPlayMode(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();
};

#endif