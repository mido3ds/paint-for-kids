#ifndef __LoadAction_h__
#define __LoadAction_h__

#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "Action.h"
#include <fstream>

class LoadAction : public Action {
public:
    LoadAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo();

private:
    bool successfull = false;
    ifstream in_file;
};

#endif /* __LoadAction_h__ */