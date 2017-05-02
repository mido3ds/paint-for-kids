#ifndef __ScrambleFind_H__
#define __ScrambleFind_H__

#include "../ApplicationManager.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class ScrambleFind : public Action {
public:
    ScrambleFind(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();
};

#endif