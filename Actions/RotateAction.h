#ifndef _ROTATE_
#define _ROTATE_

#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "Action.h"

class RotateAction : public Action {
public:
    RotateAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();

private:
    int deg;
};

#endif // !_ROTATE_
