#ifndef __SwitchPlayMode_H__
#define __SwitchPlayMode_H__

#include "Action.h"
#include "../ApplicationManager.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

//Add CRectangle Action class
class SwitchPlayMode : public Action 
{
public:
    SwitchPlayMode(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();
};

#endif