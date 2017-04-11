#ifndef __SaveAction_h__
#define __SaveAction_h__

#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "Action.h"
#include <fstream>

class SaveAction : public Action {
public:
    SaveAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute();

private:
    bool successfull = false;
    ofstream out_file;
};

#endif /* __SaveAction_h__ */
