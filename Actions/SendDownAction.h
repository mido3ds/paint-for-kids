#ifndef _DOWN_
#define _DOWN_

#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "Action.h"

#include "../GUI/Input.h"
#include "../GUI/Output.h"

class SendDownAction : public Action 
{
public:
    SendDownAction(ApplicationManager* app_p);

    virtual void ReadActionParameters();
    virtual void Execute(bool redo = false);
    virtual void Undo();

private:
	deque<int> IDs;
};

#endif // !_DOWN_